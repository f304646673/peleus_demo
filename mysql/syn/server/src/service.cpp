/*************************************************************************
    > File Name: service.cpp
    > Author: fangliang
    > Mail: f304646673@gmail.com 
    > Created Time: Tue 27 Mar 2018 01:32:52 PM CST
 ************************************************************************/
#include "service.h"
#include <brpc/server.h>

namespace peleus_demo {
namespace mysql {
namespace syn {
namespace server {

using ::peleus::plugins::mysql_conns::MysqlConns;
using ::peleus::plugins::mysql_conns::MysqlSession;

using ::brpc::ClosureGuard;
using ::brpc::Controller;

Service::Service(const char* name) :
    ::peleus::entrance::Entrance(name)
{
}

void Service::query(
    google::protobuf::RpcController* cntl_base,
    const ::peleus_demo::mysql::syn::ServiceRequest* request,
    ::peleus_demo::mysql::syn::ServiceResponse* response,
    google::protobuf::Closure* done)
{
    ClosureGuard done_guard(done);
    printf("server receive: %s\n", request->message().c_str());

    const std::string conn_name = "netdisk_reco_conn";
    const std::string command = "select feed_id from reco_feed_list where id=1000";
        
    MysqlSession session;
    int ret = MysqlConns::get_mutable_instance().query(conn_name, command, session);

    std::string response_str;
    if (ret) {
        response_str += "mysql:failed\n";
        response->set_message(response_str);
        return;
    }

    MYSQL_RES* res = session._res;
    if (!res) {
        response_str += "mysql:failed\n";
        response->set_message(response_str);
        return;
    }

    int row_size = mysql_num_rows(res);
    response_str += "mysql:suc\nresult:\n";
    for (int i = 0; i < row_size; i++) {
        parse_res(res, response_str);
    }

    response->set_message(response_str);
}

void Service::parse_res(
        MYSQL_RES* res, 
        std::string& response_str )
{
    MYSQL_ROW res_row = mysql_fetch_row(res);
    int field_size = mysql_num_fields(res); 
    for (int i = 0; i < field_size; i++) {
        response_str += std::string(res_row[i]);
    }

}

void Service::on_init(const char* conf_path) {
}

void Service::reset() {
}

}
}
}
}
