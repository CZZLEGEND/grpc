/*
 *
 * Copyright 2019 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef GRPCPP_ALTS_CONTEXT_H
#define GRPCPP_ALTS_CONTEXT_H

#include <grpc/grpc_security_constants.h>
#include <grpcpp/impl/codegen/security/auth_context.h>

#include <memory>

struct grpc_gcp_AltsContext;

namespace grpc {

// AltsContext is wrapper class for grpc_gcp_AltsContext.
class AltsContext {
 public:
  struct RpcProtocolVersions {
    struct Version {
      int major_version;
      int minor_version;
    };
    Version max_rpc_version;
    Version min_rpc_version;
  };
  explicit AltsContext(const grpc_gcp_AltsContext* ctx);
  AltsContext& operator=(const AltsContext&) = default;
  AltsContext(const AltsContext&) = default;

  grpc::string application_protocol() const;
  grpc::string record_protocol() const;
  grpc::string peer_service_account() const;
  grpc::string local_service_account() const;
  grpc_security_level security_level() const;
  RpcProtocolVersions peer_rpc_versions() const;

 private:
  // TODO(ZhenLian): Also plumb field peer_attributes when it is in use
  grpc::string application_protocol_;
  grpc::string record_protocol_;
  grpc::string peer_service_account_;
  grpc::string local_service_account_;
  grpc_security_level security_level_ = GRPC_SECURITY_NONE;
  RpcProtocolVersions peer_rpc_versions_ = {{0, 0}, {0, 0}};
};

// GetAltsContextFromAuthContext helps to get the AltsContext from AuthContext.
// Please make sure the underlying protocol is ALTS before calling this
// function. Otherwise a nullptr will be returned.
std::unique_ptr<AltsContext> GetAltsContextFromAuthContext(
    const AuthContext& auth_context);

}  // namespace grpc

#endif  // GRPCPP_ALTS_CONTEXT_H
