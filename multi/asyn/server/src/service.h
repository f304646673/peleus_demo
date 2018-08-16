/*************************************************************************
    > File Name: service.h
    > Author: fangliang
    > Mail: f304646673@gmail.com 
    > Created Time: Tue 27 Mar 2018 12:11:40 PM CST
 ************************************************************************/
#ifndef PELEUS_MULTI_ASYN_SERVER_SRC_SERVICE_H
#define PELEUS_MULTI_ASYN_SERVER_SRC_SERVICE_H
#include "multi/asyn/interface/asyn.pb.h"
#include "entrance/entrance.h"

namespace peleus_demo {
namespace multi {
namespace asyn {
namespace server {

class Service : 
    public ::peleus_demo::multi::asyn::ServiceService,
    public ::peleus::entrance::Entrance
{
public:
    explicit Service(const char* name);

public:
  virtual void query(::google::protobuf::RpcController* controller,
                       const ::peleus_demo::multi::asyn::ServiceRequest* request,
                       ::peleus_demo::multi::asyn::ServiceResponse* response,
                       ::google::protobuf::Closure* done) override;
public:
    virtual void on_init(const char* conf_path) final;
    virtual void reset() final;
};

}
}
}
}

#endif //  PELEUS_MULTI_ASYN_SERVER_SRC_SERVICE_H
