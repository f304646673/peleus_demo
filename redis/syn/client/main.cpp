/*************************************************************************
    > File Name: main.cpp
    > Author: fangliang
    > Mail: f304646673@gmail.com 
    > Created Time: Wed 28 Mar 2018 06:21:05 PM CST
 ************************************************************************/
#include <brpc/server.h>
#include <brpc/channel.h>
#include "redis/syn/interface/syn.pb.h"

using ::peleus_demo::redis::syn::RedisSynRequest;
using ::peleus_demo::redis::syn::RedisSynResponse;
using ::peleus_demo::redis::syn::RedisSynService_Stub;

int main(int argc, const char** argv) {
    brpc::Channel channel;
        
    brpc::ChannelOptions options;
    options.connection_type = "single";
    options.connect_timeout_ms = 10000;
    options.timeout_ms = 10000;
    options.max_retry = 3;
    if (channel.Init("0.0.0.0:8065", &options) != 0) {
        LOG(ERROR) << "Fail to initialize channel";
        return -1;
    }

    RedisSynService_Stub stub(static_cast<google::protobuf::RpcChannel*>(&channel));
    RedisSynRequest request;
    RedisSynResponse response;
    brpc::Controller cntl;
    request.set_message("hello peleus");

    stub.query(&cntl, &request, &response, NULL);
    printf("client receive: %s\n", response.message().c_str());
    return 0;
}
