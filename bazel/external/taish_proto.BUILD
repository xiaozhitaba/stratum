#
# Copyright 2020-present Open Networking Foundation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")
load("@rules_proto//proto:defs.bzl", "proto_library")
load("@rules_cc//cc:defs.bzl", "cc_proto_library")

licenses(["notice"])  # Apache v2

package(
    default_visibility = [ "//visibility:public" ],
)

proto_library(
  name = "taish_proto",
  srcs = ["taish/taish.proto"],
)

cc_proto_library(
  name = "taish_cc_proto",
  deps = [":taish_proto"],
)

cc_grpc_library(
  name = "taish_cc_grpc",
  srcs = [":taish_proto"],
  deps = [":taish_cc_proto"],
  grpc_only = True,
)
