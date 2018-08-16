/*************************************************************************
    > File Name: main_server.h
    > Author: fangliang
    > Mail: f304646673@gmail.com 
    > Created Time: Tue 27 Mar 2018 12:11:40 PM CST
 ************************************************************************/
#ifndef PELEUS_REDIS_ASYN_SERVER_SRC_SERVICE_H
#define PELEUS_REDIS_ASYN_SERVER_SRC_SERVICE_H
#include "redis/asyn/interface/asyn.pb.h"
#include "entrance/entrance.h"

namespace peleus_demo {
namespace redis {
namespace asyn {
namespace server {

class Service : 
    public ::peleus_demo::redis::asyn::ServiceService,
    public ::peleus::entrance::Entrance
{
public:
    explicit Service(const char* name);

public:
  virtual void query(::google::protobuf::RpcController* controller,
                       const ::peleus_demo::redis::asyn::ServiceRequest* request,
                       ::peleus_demo::redis::asyn::ServiceResponse* response,
                       ::google::protobuf::Closure* done) override;
public:
    virtual void on_init(const char* conf_path) final;
    virtual void reset() final;
};

}
}
}
}

#endif //  PELEUS_REDIS_ASYN_SERVER_SRC_SERVICE_H
