/*************************************************************************
    > File Name: inter_service.cpp
    > Author: fangliang
    > Mail: f304646673@gmail.com 
    > Created Time: Tue 27 Mar 2018 01:32:52 PM CST
 ************************************************************************/
#include "inter_service.h"
#include <brpc/server.h>

namespace peleus_demo {
namespace internal_service {
namespace syn {
namespace server {

using ::brpc::ClosureGuard;
using ::brpc::Controller;

InterServer::InterServer(const char* name) :
    ::peleus::entrance::Entrance(name)
{
}

void InterServer::query(
    google::protobuf::RpcController* cntl_base,
    const ::peleus_demo::internal_service::InterRequest* request,
    ::peleus_demo::internal_service::InterResponse* response,
    google::protobuf::Closure* done)
{
    ClosureGuard done_guard(done);
    printf("server receive: %s\n", request->message().c_str());

    std::string response_str = " inter service request is:" + request->message();

    response->set_message(response_str);
}

void InterServer::on_init(const char* conf_path) {
}

void InterServer::reset() {
}

}
}
}
}
