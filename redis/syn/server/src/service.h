/*************************************************************************
    > File Name: main_server.h
    > Author: fangliang
    > Mail: f304646673@gmail.com 
    > Created Time: Tue 27 Mar 2018 12:11:40 PM CST
 ************************************************************************/
#ifndef PELEUS_DEMO_REDIS_SERVER_SRC_SERVICE__H
#define PELEUS_DEMO_REDIS_SERVER_SRC_SERVICE__H
#include "redis/syn/interface/syn.pb.h"
#include "entrance/entrance.h"
#include "src/plugins/redis_conns/redis_conns.h"

namespace peleus_demo {
namespace redis {
namespace syn {
namespace server {

class Service : 
    public ::peleus_demo::redis::syn::ServiceService,
    public ::peleus::entrance::Entrance
{
public:
    explicit Service(const char* name);

public:
    virtual void query(::google::protobuf::RpcController* controller,
                       const ::peleus_demo::redis::syn::ServiceRequest* request,
                       ::peleus_demo::redis::syn::ServiceResponse* response,
                       ::google::protobuf::Closure* done) override;
private:

    void parse_reply(const brpc::RedisReply& reply, std::string& response_str);
    void parse_reply_array(const brpc::RedisReply& reply, std::string& response_str);
public:
    virtual void on_init(const char* conf_path) final;
    virtual void reset() final;
};

}
}
}
}

#endif //  PELEUS_DEMO_REDIS_SERVER_SRC_SERVICE__H
