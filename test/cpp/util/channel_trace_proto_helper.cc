//
//
// Copyright 2018 gRPC authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//

#include <grpc/support/port_platform.h>

#include "test/cpp/util/channel_trace_proto_helper.h"

#include <gtest/gtest.h>

#include <grpc/grpc.h>
#include <grpc/support/log.h>
#include <grpcpp/impl/codegen/config_protobuf.h>
#include <grpcpp/support/config.h>

#include "src/core/lib/gprpp/crash.h"
#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/json/json.h"
#include "src/proto/grpc/channelz/channelz.pb.h"

namespace grpc {

namespace {

// Generic helper that takes in a json string, converts it to a proto, and
// then back to json. This ensures that the json string was correctly formatted
// according to https://developers.google.com/protocol-buffers/docs/proto3#json
template <typename Message>
void VaidateProtoJsonTranslation(const std::string& json_str) {
  Message msg;
  grpc::protobuf::json::JsonParseOptions parse_options;
  // If the following line is failing, then uncomment the last line of the
  // comment, and uncomment the lines that print the two strings. You can
  // then compare the output, and determine what fields are missing.
  //
  // parse_options.ignore_unknown_fields = true;
  grpc::protobuf::util::Status s =
      grpc::protobuf::json::JsonStringToMessage(json_str, &msg, parse_options);
  EXPECT_TRUE(s.ok());
  std::string proto_json_str;
  grpc::protobuf::json::JsonPrintOptions print_options;
  // We usually do not want this to be true, however it can be helpful to
  // uncomment and see the output produced then all fields are printed.
  // print_options.always_print_primitive_fields = true;
  s = grpc::protobuf::json::MessageToJsonString(msg, &proto_json_str,
                                                print_options);
  EXPECT_TRUE(s.ok());
  // Parse JSON and re-dump to string, to make sure formatting is the
  // same as what would be generated by our JSON library.
  auto parsed_json = grpc_core::Json::Parse(proto_json_str.c_str());
  ASSERT_TRUE(parsed_json.ok()) << parsed_json.status();
  ASSERT_EQ(parsed_json->type(), grpc_core::Json::Type::kObject);
  proto_json_str = parsed_json->Dump();
  EXPECT_EQ(json_str, proto_json_str);
}

}  // namespace

namespace testing {

void ValidateChannelTraceProtoJsonTranslation(const char* json_c_str) {
  VaidateProtoJsonTranslation<grpc::channelz::v1::ChannelTrace>(json_c_str);
}

void ValidateChannelProtoJsonTranslation(const char* json_c_str) {
  VaidateProtoJsonTranslation<grpc::channelz::v1::Channel>(json_c_str);
}

void ValidateGetTopChannelsResponseProtoJsonTranslation(
    const char* json_c_str) {
  VaidateProtoJsonTranslation<grpc::channelz::v1::GetTopChannelsResponse>(
      json_c_str);
}

void ValidateGetChannelResponseProtoJsonTranslation(const char* json_c_str) {
  VaidateProtoJsonTranslation<grpc::channelz::v1::GetChannelResponse>(
      json_c_str);
}

void ValidateGetServerResponseProtoJsonTranslation(const char* json_c_str) {
  VaidateProtoJsonTranslation<grpc::channelz::v1::GetServerResponse>(
      json_c_str);
}

void ValidateSubchannelProtoJsonTranslation(const char* json_c_str) {
  VaidateProtoJsonTranslation<grpc::channelz::v1::Subchannel>(json_c_str);
}

void ValidateServerProtoJsonTranslation(const char* json_c_str) {
  VaidateProtoJsonTranslation<grpc::channelz::v1::Server>(json_c_str);
}

void ValidateGetServersResponseProtoJsonTranslation(const char* json_c_str) {
  VaidateProtoJsonTranslation<grpc::channelz::v1::GetServersResponse>(
      json_c_str);
}

}  // namespace testing
}  // namespace grpc