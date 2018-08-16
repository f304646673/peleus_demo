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
namespace redis {
namespace syn {
namespace server {

using ::::peleus::plugins::redis_conns::RedisConns;

using ::brpc::ClosureGuard;
using ::brpc::Controller;

Service::Service(const char* name) :
    ::peleus::entrance::Entrance(name)
{
}

void Service::query(
    google::protobuf::RpcController* cntl_base,
    const ::peleus_demo::redis::syn::ServiceRequest* request,
    ::peleus_demo::redis::syn::ServiceResponse* response,
    google::protobuf::Closure* done)
{
    ClosureGuard done_guard(done);
    printf("server receive: %s\n", request->message().c_str());

    const std::string conn_name = "ksarch_offline_redis";
    const std::string command = "get test_redis_key";

    // 比较奇特的现象，要在堆上分配，否则会出现溢出问题
    brpc::RedisReply* reply_ptr = new brpc::RedisReply;
    bool suc = RedisConns::get_mutable_instance().access(conn_name, command, *reply_ptr);
    const brpc::RedisReply& reply = *reply_ptr;

    std::string response_str;
    if (!suc) {
        response_str += "redis:failed\n";
        response->set_message(response_str);
        delete reply_ptr;
        return;
    }

    response_str += "redis:suc\n";
    parse_reply(reply, response_str);
    response->set_message(response_str);
    delete reply_ptr;
}

void Service::parse_reply(
        const brpc::RedisReply& reply, 
        std::string& response_str)
{
    if (reply.is_error()) {
        response_str += "type:error\n";
        response_str += reply.error_message();
        response_str += "\n";
    }
    else if (reply.is_integer()) {
        int value = reply.integer();
        std::stringstream ss;
        ss << value;
        response_str += "type:int\n";
        response_str += ss.str();
        response_str += "\n";
    }
    else if (reply.is_string()) {
        response_str += "type:string\n";
        response_str += std::string(reply.c_str());
        response_str += "\n";
    }
    else if (reply.is_array()) {
        response_str += "type:array\n";
        parse_reply_array(reply, response_str);
        response_str += "\n";
    }
    else {
        response_str += "unkown type\n";
    }
}

void Service::parse_reply_array(
        const brpc::RedisReply& reply, 
        std::string& response_str)
{
    for (size_t i = 0; i < reply.size(); i++) {
        const brpc::RedisReply& sub_reply = reply[i];
        parse_reply(sub_reply, response_str);
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
