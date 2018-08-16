/*************************************************************************
    > File Name: service.h
    > Author: fangliang
    > Mail: f304646673@gmail.com 
    > Created Time: Tue 27 Mar 2018 12:11:40 PM CST
 ************************************************************************/
#ifndef PELEUS_DEMO_HTTP_SYN_SERVER_SRC_SERVICE_H
#define PELEUS_DEMO_HTTP_SYN_SERVER_SRC_SERVICE_H
#include "http_demo/http_syn_demo/interface/http_syn_demo.pb.h"
#include "entrance/entrance.h"
#include "src/plugins/http_conns/http_conns.h"

namespace peleus_demo {
namespace http {
namespace syn {
namespace server {

class Service : 
    public ::peleus_demo::http::syn::ServiceService,
    public ::peleus::entrance::Entrance
{
public:
    explicit Service(const char* name);

public:
    virtual void query(::google::protobuf::RpcController* controller,
                       const ::peleus_demo::http::syn::ServiceRequest* request,
                       ::peleus_demo::http::syn::ServiceResponse* response,
                       ::google::protobuf::Closure* done) override;
public:
    virtual void on_init(const char* conf_path) final;
    virtual void reset() final;
};

}
}
}
}

#endif //  PELEUS_DEMO_HTTP_SYN_SERVER_SRC_SERVICE_H
