/*
Copyright (c) 2026 Lean FRO, LLC. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.
Author: Sofia Rodrigues
*/

#include "runtime/openssl/context.h"

#ifndef LEAN_EMSCRIPTEN
#include <openssl/err.h>
#endif

namespace lean {

#ifndef LEAN_EMSCRIPTEN

static inline lean_obj_res mk_ssl_ctx_io_error(char const * where) {
    unsigned long err = ERR_get_error();
    char err_buf[256];
    err_buf[0] = '\0';

    if (err != 0) {
        ERR_error_string_n(err, err_buf, sizeof(err_buf));
    }

    ERR_clear_error();

    std::string msg(where);
    if (err_buf[0] != '\0') {
        msg += ": ";
        msg += err_buf;
    }

    return lean_io_result_mk_error(lean_mk_io_user_error(mk_string(msg.c_str())));
}

static void configure_ctx_options(SSL_CTX * ctx) {
    SSL_CTX_clear_options(ctx, SSL_OP_NO_RENEGOTIATION);
}

static void lean_ssl_context_finalizer(void * ptr) {
    lean_ssl_context_object * obj = (lean_ssl_context_object*)ptr;
    if (obj->ctx != nullptr) {
        SSL_CTX_free(obj->ctx);
    }
    free(obj);
}

void initialize_openssl_context() {
    g_ssl_context_external_class = lean_register_external_class(lean_ssl_context_finalizer, [](void * obj, lean_object * f) {
        (void)obj;
        (void)f;
    });
}

static lean_obj_res mk_ssl_context(const SSL_METHOD * method) {
    SSL_CTX * ctx = SSL_CTX_new(method);
    if (ctx == nullptr) {
        return mk_ssl_ctx_io_error("SSL_CTX_new failed");
    }

    configure_ctx_options(ctx);

    lean_ssl_context_object * obj = (lean_ssl_context_object*)malloc(sizeof(lean_ssl_context_object));
    if (obj == nullptr) {
        SSL_CTX_free(ctx);
        return mk_ssl_ctx_io_error("failed to allocate SSL context object");
    }

    obj->ctx = ctx;
    lean_object * lean_obj = lean_ssl_context_object_new(obj);
    lean_mark_mt(lean_obj);
    return lean_io_result_mk_ok(lean_obj);
}

/* Std.Internal.SSL.Context.mkServer : IO Context */
extern "C" LEAN_EXPORT lean_obj_res lean_uv_ssl_ctx_mk_server() {
    return mk_ssl_context(TLS_server_method());
}

/* Std.Internal.SSL.Context.mkClient : IO Context */
extern "C" LEAN_EXPORT lean_obj_res lean_uv_ssl_ctx_mk_client() {
    return mk_ssl_context(TLS_client_method());
}

/* Std.Internal.SSL.Context.configureServer (ctx : @& Context) (certFile keyFile : @& String) : IO Unit */
extern "C" LEAN_EXPORT lean_obj_res lean_uv_ssl_ctx_configure_server(b_obj_arg ctx_obj, b_obj_arg cert_file, b_obj_arg key_file) {
    lean_ssl_context_object * obj = lean_to_ssl_context_object(ctx_obj);
    const char * cert = lean_string_cstr(cert_file);
    const char * key = lean_string_cstr(key_file);

    if (SSL_CTX_use_certificate_file(obj->ctx, cert, SSL_FILETYPE_PEM) <= 0) {
        return mk_ssl_ctx_io_error("SSL_CTX_use_certificate_file failed");
    }
    if (SSL_CTX_use_PrivateKey_file(obj->ctx, key, SSL_FILETYPE_PEM) <= 0) {
        return mk_ssl_ctx_io_error("SSL_CTX_use_PrivateKey_file failed");
    }
    if (SSL_CTX_check_private_key(obj->ctx) != 1) {
        return mk_ssl_ctx_io_error("SSL_CTX_check_private_key failed");
    }

    return lean_io_result_mk_ok(lean_box(0));
}

/* Std.Internal.SSL.Context.configureClient (ctx : @& Context) (caFile : @& String) (verifyPeer : Bool) : IO Unit */
extern "C" LEAN_EXPORT lean_obj_res lean_uv_ssl_ctx_configure_client(b_obj_arg ctx_obj, b_obj_arg ca_file, uint8_t verify_peer) {
    lean_ssl_context_object * obj = lean_to_ssl_context_object(ctx_obj);
    const char * ca = lean_string_cstr(ca_file);

    if (ca != nullptr && ca[0] != '\0') {
        if (SSL_CTX_load_verify_locations(obj->ctx, ca, nullptr) != 1) {
            return mk_ssl_ctx_io_error("SSL_CTX_load_verify_locations failed");
        }
    } else if (verify_peer) {
        if (SSL_CTX_set_default_verify_paths(obj->ctx) != 1) {
            return mk_ssl_ctx_io_error("SSL_CTX_set_default_verify_paths failed");
        }
    }

    SSL_CTX_set_verify(obj->ctx, verify_peer ? SSL_VERIFY_PEER : SSL_VERIFY_NONE, nullptr);
    return lean_io_result_mk_ok(lean_box(0));
}

#else

void initialize_openssl_context() {}

extern "C" LEAN_EXPORT lean_obj_res lean_uv_ssl_ctx_mk_server() {
    return io_result_mk_error("lean_uv_ssl_ctx_mk_server is not supported");
}

extern "C" LEAN_EXPORT lean_obj_res lean_uv_ssl_ctx_mk_client() {
    return io_result_mk_error("lean_uv_ssl_ctx_mk_client is not supported");
}

extern "C" LEAN_EXPORT lean_obj_res lean_uv_ssl_ctx_configure_server(b_obj_arg ctx_obj, b_obj_arg cert_file, b_obj_arg key_file) {
    (void)ctx_obj; (void)cert_file; (void)key_file;
    return io_result_mk_error("lean_uv_ssl_ctx_configure_server is not supported");
}

extern "C" LEAN_EXPORT lean_obj_res lean_uv_ssl_ctx_configure_client(b_obj_arg ctx_obj, b_obj_arg ca_file, uint8_t verify_peer) {
    (void)ctx_obj; (void)ca_file; (void)verify_peer;
    return io_result_mk_error("lean_uv_ssl_ctx_configure_client is not supported");
}

#endif

}
