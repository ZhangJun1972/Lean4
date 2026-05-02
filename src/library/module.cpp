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
#include "runtime/array_ref.h"
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
    // v2: original format
    // v3: dep region file paths and lib relocation table stored after header
    uint8_t version = 3;
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
    // In v3+, the fixed header is followed by:
    //   uint32_t num_deps
    //   num_deps × (uint32_t path_len, char path[path_len])
    //   uint32_t num_libs                               // closure fn ptr relocation table
    //   num_libs × (size_t base, uint32_t path_len, char path[path_len])
    //   padding to size_t alignment
    // Then the compacted data.
    // In v2, the compacted data starts immediately after the header.
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

// --- Lib table helpers for closure fn ptr relocation ---

static void write_lib_table(std::ostream & out, std::vector<lib_info> const & libs) {
    uint32_t n = libs.size();
    out.write(reinterpret_cast<char const *>(&n), sizeof(n));
    for (auto const & lib : libs) {
        out.write(reinterpret_cast<char const *>(&lib.base), sizeof(lib.base));
        uint32_t len = lib.path.size();
        out.write(reinterpret_cast<char const *>(&len), sizeof(len));
        out.write(lib.path.data(), len);
    }
}

static size_t lib_table_size(std::vector<lib_info> const & libs) {
    size_t sz = sizeof(uint32_t); // num_libs
    for (auto const & lib : libs) {
        sz += sizeof(size_t) + sizeof(uint32_t) + lib.path.size();
    }
    return sz;
}


static std::vector<std::pair<size_t, ptrdiff_t>> read_lib_table_from_fd(int fd, size_t & bytes_read) {
    std::vector<std::pair<size_t, ptrdiff_t>> relocs;
    uint32_t n;
    if (read(fd, &n, sizeof(n)) != sizeof(n)) return relocs;
    bytes_read += sizeof(n);
    if (n == 0) return relocs;
    auto current_libs = get_loaded_libs();
    for (uint32_t i = 0; i < n; i++) {
        size_t old_base;
        if (read(fd, &old_base, sizeof(old_base)) != sizeof(old_base)) break;
        uint32_t len;
        if (read(fd, &len, sizeof(len)) != sizeof(len)) break;
        std::string path(len, '\0');
        if (read(fd, &path[0], len) != static_cast<ssize_t>(len)) break;
        bytes_read += sizeof(old_base) + sizeof(len) + len;
        size_t new_base = 0;
        for (auto const & lib : current_libs) {
            if (lib.path == path) {
                new_base = lib.base;
                break;
            }
        }
        ptrdiff_t delta = static_cast<ptrdiff_t>(new_base) - static_cast<ptrdiff_t>(old_base);
        relocs.push_back({old_base, delta});
    }
    std::sort(relocs.begin(), relocs.end());
    return relocs;
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

        // Collect dep file paths: import dep regions + last prior part (transitivity handles the rest)
        std::vector<std::string> dep_paths;
        for (compacted_region * dep : compactor.dep_regions()) {
            dep_paths.push_back(dep->fname());
        }
        if (!compactor.written_fnames().empty()) {
            dep_paths.push_back(compactor.written_fnames().back());
        }

        // Compact the module data first so we know if closures are present
        // (need to know for header extension size calculation)
        // Actually, we need to reserve space before compacting. So we compact,
        // then compute sizes, then write. But the compactor buffer grows, and
        // we need to know the file_offset before compacting.
        //
        // Solution: compact first with a tentative header size, then adjust.
        // Or: assume closures might be present and always reserve space for the
        // lib table. Since the lib table is only written when has_closures(),
        // we can compute its size from the pre-built m_libs table.
        // Actually, m_libs is built once in the constructor. We can compute
        // the lib table size upfront (worst case: all libs). If no closures
        // end up being compacted, we write num_libs=0.

        // Compute extension size: dep table + lib table (worst case: all libs).
        // We reserve for the full lib table upfront since m_libs is fixed at construction
        // and we don't know until after compaction whether closures appear.
        size_t dep_table_size = sizeof(uint32_t); // num_deps
        for (std::string const & path : dep_paths) {
            dep_table_size += sizeof(uint32_t) + path.size();
        }
        // Reserve for full lib table (worst case — all loaded libraries)
        size_t max_lib_table = lib_table_size(compactor.all_libs());
        // At minimum, num_libs=0 (4 bytes)
        if (max_lib_table < sizeof(uint32_t)) max_lib_table = sizeof(uint32_t);
        size_t ext_size = dep_table_size + max_lib_table;
        size_t ext_padded = ext_size;
        if (ext_padded % sizeof(size_t) != 0) {
            ext_padded += sizeof(size_t) - (ext_padded % sizeof(size_t));
        }

        // Align compactor buffer for this file's portion
        if (compactor.size() % ALIGN != 0) {
            compactor.alloc(ALIGN - (compactor.size() % ALIGN));
        }
        size_t file_offset = compactor.size();

        // Reserve space in compactor for header + extension (so base_addr offsets are correct)
        compactor.alloc(sizeof(olean_header) + ext_padded);

        // Compact the module data
        compactor(odata);

        // Write header
        olean_header header = {};
        header.base_addr = reinterpret_cast<size_t>(compactor.base_addr()) + file_offset;
        strncpy(header.lean_version, get_short_version_string().c_str(), sizeof(header.lean_version));
        strncpy(header.githash, LEAN_GITHASH, sizeof(header.githash));
        out.write(reinterpret_cast<char *>(&header), sizeof(header));

        // Write dep table
        uint32_t num_deps = static_cast<uint32_t>(dep_paths.size());
        out.write(reinterpret_cast<char const *>(&num_deps), sizeof(num_deps));
        for (std::string const & path : dep_paths) {
            uint32_t path_len = static_cast<uint32_t>(path.size());
            out.write(reinterpret_cast<char const *>(&path_len), sizeof(path_len));
            out.write(path.data(), path_len);
        }

        // Always write the full lib table (all loaded libraries) so the
        // reserved extension size matches what the reader will parse.
        write_lib_table(out, compactor.all_libs());

        // Write padding to fill reserved extension space
        size_t written_ext = dep_table_size + lib_table_size(compactor.all_libs());
        if (written_ext < ext_padded) {
            size_t padding = ext_padded - written_ext;
            std::vector<char> zeros(padding, 0);
            out.write(zeros.data(), padding);
        }

        if (out.fail()) {
            throw exception((sstream() << "failed to create file '" << olean_fn << "'").str());
        }
        size_t data_offset = file_offset + sizeof(olean_header) + ext_padded;
        out.write(static_cast<char const *>(compactor.data()) + data_offset,
                  compactor.size() - data_offset);
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

    compactor.add_written_fname(std::string(olean_fn));
    return io_result_mk_ok(cs_obj.steal());
}

// Loads a file and its deps recursively. Appends (region, root_object) pairs to `out`,
// deps first, self last. Returns the compacted_region for this file.
static compacted_region * read_module_data_incr_core(
        std::string const & olean_fn,
        std::vector<std::pair<compacted_region *, object *>> & out) {
#ifdef LEAN_WINDOWS
    HANDLE h_file = CreateFile(olean_fn.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (h_file == INVALID_HANDLE_VALUE) {
        throw exception((sstream() << "failed to open file '" << olean_fn << "': " << GetLastError()).str());
    }
    int raw_fd = _open_osfhandle((intptr_t)h_file, _O_RDONLY);
    if (raw_fd == -1) {
        CloseHandle(h_file);
        throw exception((sstream() << "failed to convert handle to fd for '" << olean_fn << "'").str());
    }
    file_descriptor fd(raw_fd);
#else
    file_descriptor fd(open(olean_fn.c_str(), O_RDONLY));
    if (!fd) {
        throw exception((sstream() << "failed to open file '" << olean_fn << "': " << strerror(errno)).str());
    }
#endif

    struct stat st;
    if (fstat(fd.get(), &st) == -1) {
        throw exception((sstream() << "failed to stat file '" << olean_fn << "': " << strerror(errno)).str());
    }
    size_t size = st.st_size;

    olean_header default_header = {};
    olean_header header;
    if (read(fd.get(), &header, sizeof(header)) != sizeof(header)
        || memcmp(header.marker, default_header.marker, sizeof(header.marker)) != 0) {
        throw exception((sstream() << "failed to read file '" << olean_fn << "', invalid header").str());
    }
    if (header.flags != default_header.flags
#ifdef LEAN_CHECK_OLEAN_VERSION
        || strncmp(header.githash, LEAN_GITHASH, sizeof(header.githash)) != 0
#endif
    ) {
        throw exception((sstream() << "failed to read file '" << olean_fn << "', incompatible header").str());
    }
    if (header.version != default_header.version) {
        throw exception((sstream() << "failed to read file '" << olean_fn << "', incompatible header").str());
    }

    // Read dep table (v3+) and recursively load dep regions
    std::vector<compacted_region *> dep_regions;
    std::vector<std::pair<size_t, ptrdiff_t>> lib_relocs;
    size_t ext_file_size = 0;
    uint32_t num_deps;
    if (read(fd.get(), &num_deps, sizeof(num_deps)) != sizeof(num_deps)) {
        throw exception((sstream() << "failed to read dep table from '" << olean_fn << "'").str());
    }
    ext_file_size += sizeof(num_deps);
    for (uint32_t i = 0; i < num_deps; i++) {
        uint32_t path_len;
        if (read(fd.get(), &path_len, sizeof(path_len)) != sizeof(path_len)) {
            throw exception((sstream() << "failed to read dep table from '" << olean_fn << "'").str());
        }
        std::string dep_path(path_len, '\0');
        if (read(fd.get(), &dep_path[0], path_len) != static_cast<ssize_t>(path_len)) {
            throw exception((sstream() << "failed to read dep table from '" << olean_fn << "'").str());
        }
        ext_file_size += sizeof(path_len) + path_len;
        dep_regions.push_back(read_module_data_incr_core(dep_path, out));
    }

    // Read lib relocation table
    lib_relocs = read_lib_table_from_fd(fd.get(), ext_file_size);

    // Skip padding to size_t alignment
    if (ext_file_size % sizeof(size_t) != 0) {
        size_t padding = sizeof(size_t) - (ext_file_size % sizeof(size_t));
        lseek(fd.get(), padding, SEEK_CUR);
        ext_file_size += padding;
    }

    lseek(fd.get(), 0, SEEK_SET);
    char * base_addr = reinterpret_cast<char *>(header.base_addr);
    size_t data_offset = sizeof(olean_header) + ext_file_size;

    char * buffer = nullptr;
    std::function<void()> free_data;

    // If any dep region couldn't be mmap'd at its base address, or if closure relocation
    // is needed, we need writable memory for in-place pointer fixups, so don't attempt mmap.
    bool try_mmap = true;
    for (compacted_region * dep : dep_regions) {
        if (dep->begin() != dep->base_addr()) { try_mmap = false; break; }
    }
    // Check if any closure fn ptr relocation is actually needed
    bool needs_fn_reloc = false;
    for (auto const & [_, delta] : lib_relocs) {
        if (delta != 0) { needs_fn_reloc = true; break; }
    }
    if (needs_fn_reloc) try_mmap = false;

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
        buffer = static_cast<char *>(malloc(size));
        lseek(fd.get(), 0, SEEK_SET);
        if (::read(fd.get(), buffer, size) != static_cast<ssize_t>(size)) {
            free(buffer);
            throw exception((sstream() << "failed to read file '" << olean_fn << "'").str());
        }
        free_data = [=]() { free_sized(const_cast<char*>(buffer), size); };
    }

    // Include transitive dep regions (each dep's own deps)
    {
        std::vector<compacted_region *> all_deps;
        for (compacted_region * dep : dep_regions) {
            for (compacted_region * transitive : dep->dep_regions()) {
                all_deps.push_back(transitive);
            }
            all_deps.push_back(dep);
        }
        dep_regions = std::move(all_deps);
    }

    bool is_mmap = (buffer == base_addr);
    compacted_region * region = new compacted_region(
        size - data_offset, buffer + data_offset,
        base_addr + data_offset, is_mmap, free_data,
        olean_fn, std::move(dep_regions), std::move(lib_relocs));
#if defined(__has_feature)
#if __has_feature(address_sanitizer)
    __lsan_ignore_object(region);
#endif
#endif
    object * mod_data = region->read();
    out.push_back(std::make_pair(region, mod_data));
    return region;
}

extern "C" LEAN_EXPORT object * lean_read_module_data_incr(b_obj_arg ofname, object *) {
    try {
        std::vector<std::pair<compacted_region *, object *>> parts;
        read_module_data_incr_core(std::string(lean_string_cstr(ofname)), parts);
        std::vector<object_ref> res;
        for (std::pair<compacted_region *, object *> & p : parts) {
            object * pair = alloc_cnstr(0, 2, 0);
            cnstr_set(pair, 0, p.second);
            cnstr_set(pair, 1, box_size_t(reinterpret_cast<size_t>(p.first)));
            res.push_back(object_ref(pair));
        }
        return io_result_mk_ok(to_array(res));
    } catch (exception & ex) {
        return io_result_mk_error((sstream() << "failed to read '" << lean_string_cstr(ofname) << "': " << ex.what()).str());
    }
}
}
