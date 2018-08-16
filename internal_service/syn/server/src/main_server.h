/*************************************************************************
    > File Name: main_service.h
    > Author: fangliang
    > Mail: f304646673@gmail.com 
    > Created Time: Tue 27 Mar 2018 12:11:40 PM CST
 ************************************************************************/
#ifndef PELEUS_DEMO_INTERNAL_SERVICE_SYN_SERVER_SRC_MAIN_SERVER_H
#define PELEUS_DEMO_INTERNAL_SERVICE_SYN_SERVER_SRC_MAIN_SERVER_H
#include "internal_service/syn/interface/main_service.pb.h"
#include "entrance/entrance.h"

namespace peleus_demo {
namespace internal_service {
namespace syn {
namespace server {

class MainServer : 
    public ::peleus_demo::internal_service::syn::MainService,
    public ::peleus::entrance::Entrance
{
public:
    explicit MainServer(const char* name);

public:
  virtual void query(::google::protobuf::RpcController* controller,
                       const ::peleus_demo::internal_service::MainRequest* request,
                       ::peleus_demo::internal_service::MainResponse* response,
                       ::google::protobuf::Closure* done) override;
public:
    virtual void on_init(const char* conf_path) final;
    virtual void reset() final;
};

}
}
}
}

#endif //  PELEUS_DEMO_INTERNAL_SERVICE_SYN_SERVER_SRC_MAIN_SERVER_H
