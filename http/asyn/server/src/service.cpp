/*************************************************************************
    > File Name: service.cpp
    > Author: fangliang
    > Mail: f304646673@gmail.com 
    > Created Time: Tue 27 Mar 2018 01:32:52 PM CST
 ************************************************************************/
#include "service.h"
#include <brpc/server.h>
#include "entrance/semi_sync_rpc.h"
#include "src/plugins/http_visitor/interface/http_visitor_service.pb.h"

namespace peleus_ {
namespace http {
namespace asyn {
namespace server {

using ::brpc::ClosureGuard;
using ::brpc::Controller;

using ::peleus::entrance::SemiSyncRpc;
using ::peleus::plugins::HttpVisitorServiceRequest;
using ::peleus::plugins::HttpVisitorServiceResponse;
using ::peleus::plugins::HttpVisitorService_Stub;

Service::Service(const char* name) :
    ::peleus::entrance::Entrance(name)
{
}

void Service::query(
    google::protobuf::RpcController* cntl_base,
    const ::peleus::::http::asyn::HttpAsynRequest* request,
    ::peleus_demo::http::asyn::HttpAsynResponse* response,
    google::protobuf::Closure* done)
{
    ClosureGuard done_guard(done);
    printf("server receive: %s\n", request->message().c_str());

    HttpVisitorServiceRequest http_request;
    http_request.set_conn_name("163_com");
    http_request.set_uri("/");
    http_request.set_post(false);

    HttpVisitorServiceResponse http_response;
    SemiSyncRpc sync;
    sync.add<HttpVisitorService_Stub>(NULL, &HttpVisitorService_Stub::query,
            &http_request, &http_response);
    sync.join();

    std::string response_str;
    if (0 != http_response.error_code()) {
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
