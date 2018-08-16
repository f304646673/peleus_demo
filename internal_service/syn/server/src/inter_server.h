/*************************************************************************
    > File Name: inter_server.h
    > Author: fangliang
    > Mail: f304646673@gmail.com 
    > Created Time: Tue 27 Mar 2018 12:11:40 PM CST
 ************************************************************************/
#ifndef PELEUS_DEMO_INTERNAL_SERVICE_SYN_SERVER_SRC_INTER_SERVER_H
#define PELEUS_DEMO_INTERNAL_SERVICE_SYN_SERVER_SRC_INTER_SERVER_H
#include "internal_service/syn/interface/inter_service.pb.h"
#include "entrance/entrance.h"

namespace peleus_demo {
namespace internal_service {
namespace syn {
namespace server {

class InterServer : 
    public ::peleus_demo::internal_service::syn::InterService,
    public ::peleus::entrance::Entrance
{
public:
    explicit InterServer(const char* name);

public:
  virtual void query(::google::protobuf::RpcController* controller,
                       const ::peleus_demo::internal_service::InterRequest* request,
                       ::peleus_demo::internal_service::InterResponse* response,
                       ::google::protobuf::Closure* done) override;
public:
    virtual void on_init(const char* conf_path) final;
    virtual void reset() final;
};

}
}
}
}

#endif //  PELEUS_DEMO_INTERNAL_SERVICE_SYN_SERVER_SRC_INTER_SERVER_H
