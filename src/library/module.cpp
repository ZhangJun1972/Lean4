/*
Copyright (c) 2014-2015 Microsoft Corporation. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.

Authors: Leonardo de Moura, Gabriel Ebner, Sebastian Ullrich

.olean serialization and deserialization.
*/
#include <unordered_map>
#include <vector>
#include <utility>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <sys/stat.h>
#include "runtime/thread.h"
#include "runtime/interrupt.h"
#include "runtime/sstream.h"
#include "runtime/hash.h"
#include "runtime/io.h"
#include "runtime/compact.h"
#include "runtime/buffer.h"
#include "runtime/string_ref.h"
#include "util/io.h"
#include "util/name_map.h"
#include "library/module.h"
#include "library/constants.h"
#include "library/time_task.h"
#include "library/util.h"
#include "githash.h"

#ifdef LEAN_WINDOWS
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#else
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#endif

#if defined(__has_feature)
#if __has_feature(address_sanitizer)
#include <sanitizer/lsan_interface.h>
#endif
#endif

namespace lean {

/** Trivial RAII wrapper for file descriptors so we don't have to worry about `close` management. */
class file_descriptor {
private:
    int m_fd;
public:
    explicit file_descriptor(int fd) : m_fd(fd) {}

    // It should not be copyable
    file_descriptor(const file_descriptor&) = delete;
    file_descriptor& operator=(const file_descriptor&) = delete;

    file_descriptor(file_descriptor&& other) noexcept : m_fd(other.m_fd) {
        other.m_fd = -1;
    }

    ~file_descriptor() {
        if (m_fd != -1) {
            close(m_fd);
        }
    }

    int get() const { return m_fd; }
    operator bool() const { return m_fd != -1; }
};

/** On-disk format of a .olean file. */
struct olean_header {
    // 5 bytes: magic number
    char marker[5] = {'o', 'l', 'e', 'a', 'n'};
    // 1 byte: version, incremented on structural changes to header
    uint8_t version = 2;
    // 1 byte of flags:
    // * bit 0: whether persisted bignums use GMP or Lean-native encoding
    // * bit 1-7: reserved
    uint8_t flags =
#ifdef LEAN_USE_GMP
        0b1;
#else
        0b0;
#endif
    // 33 bytes: Lean version string, padded with '\0' to the right
    // e.g. "4.12.0-nightly-2024-10-18". Other suffixes after the version
    // triple currently in use are `-rcN` for some `N` and `-pre` for any
    // other non-release commit. Not necessarily null-terminated.
    char lean_version[33];
    // 81b008650766442a0dfa9faa796e4588c9d7d3a1
    // 40 bytes: build githash, padded with `\0` to the right
    char githash[40];
    // address at which the beginning of the file (including header) is attempted to be mmapped
    size_t base_addr;
    // payload, a serialize Lean object graph; `size_t` has same alignment requirements as Lean objects
    size_t data[];
};
// make sure we don't have any padding bytes, which also ensures `data` is properly aligned
static_assert(sizeof(olean_header) == 5 + 1 + 1 + 33 + 40 + sizeof(size_t), "olean_header must be packed");


// --- Compactor external object: wraps a live object_compactor for incremental compaction ---
// Keeping the full compactor alive preserves both the obj_table (pointer-identity dedup)
// and the max_sharing_table (structural dedup) across sequential saves.

static lean_external_class * g_compactor_class = nullptr;

static void compactor_finalizer(void * data) {
    delete static_cast<object_compactor *>(data);
}

static void compactor_foreach(void *, b_lean_obj_arg) {
    // no Lean object references to trace
}

static void ensure_compactor_class() {
    if (!g_compactor_class) {
        g_compactor_class = lean_register_external_class(compactor_finalizer, compactor_foreach);
    }
}

static lean_object * mk_compactor(void * base_addr, std::vector<compacted_region *> dep_regions) {
    ensure_compactor_class();
    return lean_alloc_external(g_compactor_class, new object_compactor(base_addr, std::move(dep_regions)));
}

static object_compactor * to_compactor(lean_object * o) {
    return static_cast<object_compactor *>(lean_get_external_data(o));
}

// Extract compacted_region pointers from an Array CompactedRegion
static std::vector<compacted_region *> extract_dep_regions(b_obj_arg odep_regions) {
    std::vector<compacted_region *> result;
    size_t n = lean_array_size(odep_regions);
    result.reserve(n);
    for (size_t i = 0; i < n; i++) {
        result.push_back(reinterpret_cast<compacted_region *>(lean_unbox_usize(lean_array_get_core(odep_regions, i))));
    }
    return result;
}

extern "C" LEAN_EXPORT object * lean_save_module_data_incr(b_obj_arg ofname, b_obj_arg mod, b_obj_arg odata,
                                                           b_obj_arg odep_regions, obj_arg oprev, object *) {
    // `mmap` addresses must be page-aligned. The default (non-huge) page size on x86-64 is
    // 4KB. `MapViewOfFileEx` addresses must be aligned to the "memory allocation granularity",
    // which is 64KB.
    const size_t ALIGN = 1LL<<16;

    // Reuse compactor from previous Compactor, or create a new one.
    // Keeping the compactor alive preserves both obj_table and max_sharing_table.
    object_ref cs_obj;
    if (lean_obj_tag(oprev) == 1) {
        // Option.some — reuse existing compactor
        cs_obj = object_ref(lean_ctor_get(oprev, 0), true);
        lean_dec(oprev);
    } else {
        // Option.none — create new compactor with base_addr derived from mod.
        // Derive a base address that is uniformly distributed but deterministic, and should most
        // likely work for `mmap` on all interesting platforms.
        // NOTE: an overlapping/non-compatible base address does not prevent the module from being
        // imported, merely from using `mmap` for that.
        // Start with a hash of the module name. While our string hash is a dubious 32-bit
        // algorithm, the mixing of multiple `Name` parts seems to result in a nicely distributed
        // 64-bit output.
        lean_dec(oprev);
        size_t base_addr = name(mod, true).hash();
        // x86-64 user space is currently limited to the lower 47 bits
        // https://en.wikipedia.org/wiki/X86-64#Virtual_address_space_details
        // On Linux at least, the stack grows down from ~0x7fff... followed by shared libraries,
        // so reserve a bit of space for them (0x7fff...-0x7f00... = 1TB)
        base_addr = base_addr % 0x7f0000000000;
        base_addr = base_addr & ~(ALIGN - 1);
        std::vector<compacted_region *> dep_regions = extract_dep_regions(odep_regions);
        cs_obj = object_ref(mk_compactor(reinterpret_cast<void *>(base_addr), std::move(dep_regions)));
    }

    object_compactor & compactor = *to_compactor(cs_obj.raw());

    char const * olean_fn = lean_string_cstr(ofname);
    // We first write to a temp file and then move it to the correct path (possibly deleting an
    // older file) so that we neither expose partially-written files nor modify possibly
    // memory-mapped files.
#ifdef LEAN_WINDOWS
    uint32_t pid = GetCurrentProcessId();
#else
    uint32_t pid = getpid();
#endif
    std::string olean_tmp_fn = std::string(olean_fn) + ".tmp." + std::to_string(pid);

    try {
        std::ofstream out(olean_tmp_fn, std::ios_base::binary);

        if (compactor.size() % ALIGN != 0) {
            compactor.alloc(ALIGN - (compactor.size() % ALIGN));
        }
        size_t file_offset = compactor.size();

        compactor.alloc(sizeof(olean_header));
        // see/sync with file format description above
        olean_header header = {};
        header.base_addr = reinterpret_cast<size_t>(compactor.base_addr()) + file_offset;
        strncpy(header.lean_version, get_short_version_string().c_str(), sizeof(header.lean_version));
        strncpy(header.githash, LEAN_GITHASH, sizeof(header.githash));
        out.write(reinterpret_cast<char *>(&header), sizeof(header));

        compactor(odata);

        if (out.fail()) {
            throw exception((sstream() << "failed to create file '" << olean_fn << "'").str());
        }
        out.write(static_cast<char const *>(compactor.data()) + file_offset + sizeof(olean_header),
                  compactor.size() - file_offset - sizeof(olean_header));
        out.close();
    } catch (exception & ex) {
        std::remove(olean_tmp_fn.c_str());
        return io_result_mk_error((sstream() << "failed to write '" << olean_fn << "': " << ex.what()).str());
    }

    // Atomic rename
    while (std::rename(olean_tmp_fn.c_str(), olean_fn) != 0) {
#ifdef LEAN_WINDOWS
        if (errno == EEXIST) {
            // Memory-mapped files can be deleted starting with Windows 10 using "POSIX semantics"
            HANDLE h_olean_fn = CreateFile(olean_fn, GENERIC_READ | DELETE, FILE_SHARE_READ | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
            if (h_olean_fn == INVALID_HANDLE_VALUE) {
                return io_result_mk_error((sstream() << "failed to open '" << olean_fn << "': " << GetLastError()).str());
            }
            FILE_DISPOSITION_INFO_EX fdi = { FILE_DISPOSITION_FLAG_DELETE | FILE_DISPOSITION_FLAG_POSIX_SEMANTICS };
            if (SetFileInformationByHandle(h_olean_fn, static_cast<FILE_INFO_BY_HANDLE_CLASS>(21) /* FileDispositionInfoEx */, &fdi, sizeof(fdi)) != 0) {
                lean_always_assert(CloseHandle(h_olean_fn));
                continue;
            } else {
                return io_result_mk_error((sstream() << "failed to delete '" << olean_fn << "': " << GetLastError()).str());
            }
        }
#endif
        return io_result_mk_error((sstream() << "failed to write '" << olean_fn << "': " << errno << " " << strerror(errno)).str());
    }

    return io_result_mk_ok(cs_obj.steal());
}

extern "C" LEAN_EXPORT object * lean_read_module_data_incr(b_obj_arg ofname, b_obj_arg odep_regions, object *) {
    char const * olean_fn = lean_string_cstr(ofname);
    std::vector<compacted_region *> dep_regions = extract_dep_regions(odep_regions);

    try {
#ifdef LEAN_WINDOWS
        // `FILE_SHARE_DELETE` is necessary to allow the file to (be marked to) be deleted while in use
        HANDLE h_file = CreateFile(olean_fn, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (h_file == INVALID_HANDLE_VALUE) {
            return io_result_mk_error((sstream() << "failed to open file '" << olean_fn << "': " << GetLastError()).str());
        }
        int raw_fd = _open_osfhandle((intptr_t)h_file, _O_RDONLY);
        if (raw_fd == -1) {
            CloseHandle(h_file);
            return io_result_mk_error((sstream() << "failed to convert handle to fd for '" << olean_fn << "'").str());
        }
        file_descriptor fd(raw_fd);
#else
        file_descriptor fd(open(olean_fn, O_RDONLY));
        if (!fd) {
            return io_result_mk_error((sstream() << "failed to open file '" << olean_fn << "': " << strerror(errno)).str());
        }
#endif

        struct stat st;
        if (fstat(fd.get(), &st) == -1) {
            return io_result_mk_error((sstream() << "failed to stat file '" << olean_fn << "': " << strerror(errno)).str());
        }
        size_t size = st.st_size;

        olean_header default_header = {};
        olean_header header;
        if (read(fd.get(), &header, sizeof(header)) != sizeof(header)
            || memcmp(header.marker, default_header.marker, sizeof(header.marker)) != 0) {
            return io_result_mk_error((sstream() << "failed to read file '" << olean_fn << "', invalid header").str());
        }
        lseek(fd.get(), 0, SEEK_SET);
        if (header.version != default_header.version || header.flags != default_header.flags
#ifdef LEAN_CHECK_OLEAN_VERSION
            || strncmp(header.githash, LEAN_GITHASH, sizeof(header.githash)) != 0
#endif
        ) {
            return io_result_mk_error((sstream() << "failed to read file '" << olean_fn << "', incompatible header").str());
        }
        char * base_addr = reinterpret_cast<char *>(header.base_addr);

        char * buffer = nullptr;
        std::function<void()> free_data;

        // If any dep region couldn't be mmap'd at its base address, we need writable memory
        // for in-place pointer fixups, so don't attempt mmap.
        bool try_mmap = true;
        for (compacted_region * dep : dep_regions) {
            if (dep->begin() != dep->base_addr()) { try_mmap = false; break; }
        }

#ifdef LEAN_MMAP
        if (try_mmap) {
#ifdef LEAN_WINDOWS
            HANDLE h_map = CreateFileMapping(h_file, NULL, PAGE_READONLY, 0, 0, NULL);
            if (h_map != NULL) {
                buffer = static_cast<char *>(MapViewOfFileEx(h_map, FILE_MAP_READ, 0, 0, 0, base_addr));
                lean_always_assert(CloseHandle(h_map));
                if (buffer && buffer == base_addr) {
                    free_data = [=]() { lean_always_assert(UnmapViewOfFile(base_addr)); };
                } else if (buffer) {
                    lean_always_assert(UnmapViewOfFile(buffer));
                    buffer = nullptr;
                }
            }
#else
            buffer = static_cast<char *>(mmap(base_addr, size, PROT_READ, MAP_PRIVATE, fd.get(), 0));
            if (buffer != MAP_FAILED && buffer == base_addr) {
                free_data = [=]() { lean_always_assert(munmap(buffer, size) == 0); };
            } else {
                if (buffer != MAP_FAILED) munmap(buffer, size);
                buffer = nullptr;
            }
#endif
        }
#endif

        if (!buffer) {
            // Fallback: malloc and read
            buffer = static_cast<char *>(malloc(size));
            lseek(fd.get(), 0, SEEK_SET);
            if (::read(fd.get(), buffer, size) != static_cast<ssize_t>(size)) {
                free(buffer);
                return io_result_mk_error((sstream() << "failed to read file '" << olean_fn << "'").str());
            }
            free_data = [=]() { free_sized(const_cast<char*>(buffer), size); };
        }

        bool is_mmap = (buffer == base_addr);
        compacted_region * region = new compacted_region(
            size - sizeof(olean_header), buffer + sizeof(olean_header),
            base_addr + sizeof(olean_header), is_mmap, free_data, dep_regions);
#if defined(__has_feature)
#if __has_feature(address_sanitizer)
        __lsan_ignore_object(region);
#endif
#endif
        object * mod_data = region->read();
        object * result = alloc_cnstr(0, 2, 0);
        cnstr_set(result, 0, mod_data);
        cnstr_set(result, 1, box_size_t(reinterpret_cast<size_t>(region)));
        return io_result_mk_ok(result);
    } catch (exception & ex) {
        return io_result_mk_error((sstream() << "failed to read '" << olean_fn << "': " << ex.what()).str());
    }
}
}
