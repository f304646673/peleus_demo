/*************************************************************************
    > File Name: service.h
    > Author: fangliang
    > Mail: f304646673@gmail.com 
    > Created Time: Tue 27 Mar 2018 12:11:40 PM CST
 ************************************************************************/
#ifndef PELEUS_SERVER_SRC_SERVER_service_H
#define PELEUS_SERVER_SRC_SERVER_service_H
#include "no_inter_service_demo/interface/no_inter_service_demo.pb.h"
#include "entrance/entrance.h"

namespace peleus_demo {
namespace no_inter_service {
namespace syn {
namespace server {

class NoInterService : 
    public ::peleus_demo::no_inter_service::NoInterServiceService,
    public ::peleus::entrance::Entrance
{
public:
    explicit NoInterService(const char* name);

public:
  virtual void query(::google::protobuf::RpcController* controller,
                       const ::peleus_demo::no_inter_service::NoInterServiceRequest* request,
                       ::peleus_demo::no_inter_service::NoInterServiceResponse* response,
                       ::google::protobuf::Closure* done) override;
public:
    virtual void on_init(const char* conf_path) final;
    virtual void reset() final;
};

}
}
}
}

#endif //  PELEUS_SERVER_SRC_SERVER_service_H
