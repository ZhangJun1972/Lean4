/*
Copyright (c) 2026 Lean FRO, LLC. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.
Author: Sofia Rodrigues
*/
#pragma once

#include <lean/lean.h>
#include "runtime/io.h"
#include "runtime/object.h"
#include "runtime/openssl.h"

#ifndef LEAN_EMSCRIPTEN
#include <openssl/ssl.h>
#endif

namespace lean {

static lean_external_class * g_ssl_context_external_class = nullptr;
void initialize_openssl_context();

#ifndef LEAN_EMSCRIPTEN
typedef struct {
    SSL_CTX * ctx;
} lean_ssl_context_object;

static inline lean_object * lean_ssl_context_object_new(lean_ssl_context_object * c) {
    return lean_alloc_external(g_ssl_context_external_class, c);
}
static inline lean_ssl_context_object * lean_to_ssl_context_object(lean_object * o) {
    return (lean_ssl_context_object*)(lean_get_external_data(o));
}
#endif

extern "C" LEAN_EXPORT lean_obj_res lean_uv_ssl_ctx_mk_server();
extern "C" LEAN_EXPORT lean_obj_res lean_uv_ssl_ctx_mk_client();
extern "C" LEAN_EXPORT lean_obj_res lean_uv_ssl_ctx_configure_server(b_obj_arg ctx, b_obj_arg cert_file, b_obj_arg key_file);
extern "C" LEAN_EXPORT lean_obj_res lean_uv_ssl_ctx_configure_client(b_obj_arg ctx, b_obj_arg ca_file, uint8_t verify_peer);

}
