/*************************************************************************
    > File Name: service.cpp
    > Author: fangliang
    > Mail: f304646673@gmail.com 
    > Created Time: Tue 27 Mar 2018 01:32:52 PM CST
 ************************************************************************/
#include "service.h"
#include <brpc/server.h>
#include "entrance/semi_sync_rpc.h"
#include "src/plugins/redis_visitor/interface/redis_visitor_service.pb.h"

namespace peleus_demo {
namespace redis {
namespace asyn {
namespace server {

using ::peleus::entrance::SemiSyncRpc;
using ::peleus::plugins::RedisVisitorServiceRequest;
using ::peleus::plugins::RedisVisitorServiceResponse;
using ::peleus::plugins::RedisVisitorService_Stub;
using ::peleus::plugins::RedisVisitorReply;

using ::brpc::ClosureGuard;
using ::brpc::Controller;

Service::Service(const char* name) :
    ::peleus::entrance::Entrance(name)
{
}

void Service::query(
    google::protobuf::RpcController* cntl_base,
    const ::peleus_demo::redis::asyn::ServiceRequest* request,
    ::peleus_demo::redis::asyn::ServiceResponse* response,
    google::protobuf::Closure* done)
{
    ClosureGuard done_guard(done);
    printf("server receive: %s\n", request->message().c_str());

    RedisVisitorServiceRequest redis_request;
    RedisVisitorServiceResponse redis_response;
    redis_request.set_command("get test_redis_key");
    redis_request.set_conn_name("ksarch_offline_redis");

    SemiSyncRpc sync;
    sync.add<RedisVisitorService_Stub>(NULL, &RedisVisitorService_Stub::query,
            &redis_request, &redis_response);
    sync.join();

    std::string response_str;

    if (redis_response.suc()) {
        response_str += "redis:suc\nresult:\n";
        const RedisVisitorReply& rp = redis_response.reply();
        if (rp.type() == RedisVisitorReply::STRING) {
            response_str += rp.c_str();
        }
    }
    else {
        response_str += "redis:failed\n";
    }

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
