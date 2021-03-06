/*************************************************************************
    > File Name: service.cpp
    > Author: fangliang
    > Mail: f304646673@gmail.com 
    > Created Time: Tue 27 Mar 2018 01:32:52 PM CST
 ************************************************************************/
#include "service.h"
#include <brpc/server.h>
#include <sstream>

namespace peleus_demo {
namespace http {
namespace syn {
namespace server {

using ::brpc::ClosureGuard;
using ::brpc::Controller;

using ::peleus::plugins::HttpRequest;
using ::peleus::plugins::HttpResponse;
using ::::peleus::plugins::http_conns::HttpConns;

Service::Service(const char* name) :
    ::peleus::entrance::Entrance(name)
{
}

void Service::query(
    google::protobuf::RpcController* cntl_base,
    const ::peleus_demo::http::syn::ServiceRequest* request,
    ::peleus_demo::http::syn::ServiceResponse* response,
    google::protobuf::Closure* done)
{
    ClosureGuard done_guard(done);
    printf("server receive: %s\n", request->message().c_str());

    HttpRequest http_request;
    http_request.set_conn_name("163_com");
    http_request.set_uri("/");
    http_request.set_post(false);

    HttpResponse http_response;
    bool suc = HttpConns::get_mutable_instance().access(http_request, http_response);
    std::string response_str;
    if (!suc) {
        response_str += "http:failed\n";
        response_str += "error_code:";
        response_str += http_response.error_code();
        response->set_message(response_str);
        return;
    }

    response_str += "http:suc\n";
    response_str += http_response.response();
    response->set_message(response_str);
}

void Service::on_init(const char* conf_path) {
}

void Service::reset() {
}

}
}
}
}
