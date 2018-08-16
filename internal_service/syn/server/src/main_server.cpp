/*************************************************************************
    > File Name: main_service.cpp
    > Author: fangliang
    > Mail: f304646673@gmail.com 
    > Created Time: Tue 27 Mar 2018 01:32:52 PM CST
 ************************************************************************/
#include "main_service.h"
#include <brpc/server.h>
#include "entrance/semi_sync_rpc.h"
#include "internal_service/interface/inter_service.pb.h"

namespace peleus_demo {
namespace internal_service {
namespace syn {
namespace server {

using ::brpc::ClosureGuard;
using ::brpc::Controller;
using ::::peleus::entrance::SemiSyncRpc;
using ::peleus_demo::internal_service::InterRequest;
using ::peleus_demo::internal_service::InterResponse;
using ::peleus_demo::internal_service::InterService_Stub;

MainServer::MainServer(const char* name) :
    ::peleus::entrance::Entrance(name)
{
}

void MainServer::query(
    google::protobuf::RpcController* cntl_base,
    const ::peleus_demo::internal_service::MainRequest* request,
    ::peleus_demo::internal_service::MainResponse* response,
    google::protobuf::Closure* done)
{
    ClosureGuard done_guard(done);
    printf("server receive: %s\n", request->message().c_str());
    
    InterRequest inter_request;
    InterResponse inter_response;
    inter_request.set_message(request->message());
    SemiSyncRpc sync;
    sync.add<Inter_Stub>(NULL, &InterService_Stub::query,
            &inter_request, &inter_response);
    sync.join();
    std::string response_str = "request is:" + inter_response.message();

    response->set_message(response_str);
}

void MainServer::on_init(const char* conf_path) {
}

void MainServer::reset() {
}

}
}
}
}
