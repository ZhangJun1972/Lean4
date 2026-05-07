/-
Copyright (c) 2026 Lean FRO, LLC. All rights reserved.
Released under Apache 2.0 license as described in the file LICENSE.
Authors: Sofia Rodrigues
-/
module

prelude
public import Init.System.Promise

public section

namespace Std.Internal.SSL

/--
Distinguishes server-side from client-side TLS contexts and sessions at the type level.
-/
inductive Role where
  | server
  | client

private opaque ContextServerImpl : NonemptyType.{0}
private opaque ContextClientImpl : NonemptyType.{0}

/--
Server-side TLS context (`SSL_CTX` configured with `TLS_server_method`).
-/
def Context.Server : Type := ContextServerImpl.type

/--
Client-side TLS context (`SSL_CTX` configured with `TLS_client_method`).
-/
def Context.Client : Type := ContextClientImpl.type

instance : Nonempty Context.Server := ContextServerImpl.property
instance : Nonempty Context.Client := ContextClientImpl.property

namespace Context

namespace Server

/--
Creates a new server-side TLS context using `TLS_server_method`.
-/
@[extern "lean_uv_ssl_ctx_mk_server"]
opaque mk : IO Context.Server

/--
Loads a PEM certificate and private key into a server context.
-/
@[extern "lean_uv_ssl_ctx_configure_server"]
opaque configure (ctx : @& Context.Server) (certFile : @& String) (keyFile : @& String) : IO Unit

end Server

namespace Client

/--
Creates a new client-side TLS context using `TLS_client_method`.
-/
@[extern "lean_uv_ssl_ctx_mk_client"]
opaque mk : IO Context.Client

/--
Configures CA trust anchors and peer verification for a client context.
`caFile` may be empty to use platform default trust anchors.
-/
@[extern "lean_uv_ssl_ctx_configure_client"]
opaque configure (ctx : @& Context.Client) (caFile : @& String) (verifyPeer : Bool) : IO Unit

end Client

end Context

end Std.Internal.SSL
