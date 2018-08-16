/*************************************************************************
    > File Name: service.h
    > Author: fangliang
    > Mail: f304646673@gmail.com 
    > Created Time: Tue 27 Mar 2018 12:11:40 PM CST
 ************************************************************************/
#ifndef PELEUS_DEMO_HTTP_ASYN_SERVER_SRC_SERVICE_H
#define PELEUS_DEMO_HTTP_ASYN_SERVER_SRC_SERVICE_H
#include "http/asyn/interface/asyn.pb.h"
#include "entrance/entrance.h"

namespace peleus_demo {
namespace http {
namespace asyn {
namespace server {

class Service : 
    public ::peleus_demo::http::asyn::HttpAsynService,
    public ::peleus::entrance::Entrance
{
public:
    explicit Service(const char* name);

public:
  virtual void query(::google::protobuf::RpcController* controller,
                       const ::peleus::http::asyn::HttpAsynRequest* request,
                       ::peleus::http::asyn::HttpAsynResponse* response,
                       ::google::protobuf::Closure* done) override;
public:
    virtual void on_init(const char* conf_path) final;
    virtual void reset() final;
};

}
}
}
}

#endif //  PELEUS_HTTP_ASYN_SERVER_SRC_SERVIICE_H
