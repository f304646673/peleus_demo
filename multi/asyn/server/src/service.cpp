/*************************************************************************
    > File Name: service.cpp
    > Author: fangliang
    > Mail: f304646673@gmail.com 
    > Created Time: Tue 27 Mar 2018 01:32:52 PM CST
 ************************************************************************/
#include "service.h"
#include <brpc/server.h>
#include "entrance/semi_sync_rpc.h"
#include "src/plugins/mysql_visitor/interface/mysql_visitor_service.pb.h"
#include "src/plugins/redis_visitor/interface/redis_visitor_service.pb.h"

namespace peleus_demo {
namespace multi {
namespace asyn {
namespace server {

using ::peleus::entrance::SemiSyncRpc;
using ::peleus::plugins::MysqlVisitorServiceRequest;
using ::peleus::plugins::MysqlVisitorServiceResponse;
using ::peleus::plugins::MysqlVisitorService_Stub;
using ::peleus::plugins::MysqlVisitorRow;

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
    const ::peleus_demo::multi::asyn::ServiceRequest* request,
    ::peleus_demo::multi::asyn::ServiceResponse* response,
    google::protobuf::Closure* done)
{
    ClosureGuard done_guard(done);
    printf("server receive: %s\n", request->message().c_str());

    MysqlVisitorServiceRequest mysql_request;
    MysqlVisitorServiceResponse mysql_response;
    mysql_request.set_command("select feed_id from reco_feed_list where id=1000");
    mysql_request.set_conn_name("netdisk_reco_conn");

    RedisVisitorServiceRequest redis_request;
    RedisVisitorServiceResponse redis_response;
    redis_request.set_command("get test_redis_key");
    redis_request.set_conn_name("ksarch_offline_redis");

    SemiSyncRpc sync;
    sync.add<MysqlVisitorService_Stub>(NULL, &MysqlVisitorService_Stub::query,
            &mysql_request, &mysql_response);
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

    response_str += "\n";

    if (mysql_response.suc()) {
        response_str += "mysql:suc\nresult:\n";
        auto size = mysql_response.rows_size();
        for (auto i = 0; i < size; i++) {
            const MysqlVisitorRow& row = mysql_response.rows(i);
            auto column_size = row.column_size();
            for (auto j = 0; j < column_size; j++) {
                response_str += row.column(j);
                response_str += "\n";
            }
        }
    }
    else {
        response_str += "mysql:failed\n";
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
