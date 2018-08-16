/*************************************************************************
    > File Name: service.cpp
    > Author: fangliang
    > Mail: f304646673@gmail.com 
    > Created Time: Tue 27 Mar 2018 01:32:52 PM CST
 ************************************************************************/
#include "service.h"
#include <brpc/server.h>

namespace peleus_demo {
namespace no_inter_service {
namespace syn {
namespace server {

using ::brpc::ClosureGuard;
using ::brpc::Controller;

NoInterService::NoInterService(const char* name) :
    ::peleus::entrance::Entrance(name)
{
}

void NoInterService::query(
    google::protobuf::RpcController* cntl_base,
    const ::peleus_demo::no_inter_service::NoInterServiceRequest* request,
    ::peleus_demo::no_inter_service::NoInterServiceResponse* response,
    google::protobuf::Closure* done)
{
    ClosureGuard done_guard(done);
    printf("server receive: %s\n", request->message().c_str());

    std::string response_str = "request is:" + request->message();

    response->set_message(response_str);
}

void NoInterService::on_init(const char* conf_path) {
}

void NoInterService::reset() {
}

}
}
}
}
