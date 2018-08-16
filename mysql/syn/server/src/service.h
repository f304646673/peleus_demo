/*************************************************************************
    > File Name: service.h
    > Author: fangliang
    > Mail: f304646673@gmail.com 
    > Created Time: Tue 27 Mar 2018 12:11:40 PM CST
 ************************************************************************/
#ifndef PELEUS_MYSQL_SYN_SERVER_SRC_SERVICE_H
#define PELEUS_MYSQL_SYN_SERVER_SRC_SERVICE_H
#include "mysql/syn/interface/syn.pb.h"
#include "entrance/entrance.h"
#include "src/plugins/mysql_conns/mysql_conns.h"

namespace peleus_demo {
namespace mysql {
namespace syn {
namespace server {

class Service : 
    public ::peleus_demo::mysql::syn::ServiceService,
    public ::peleus::entrance::Entrance
{
public:
    explicit Service(const char* name);

public:
    virtual void query(::google::protobuf::RpcController* controller,
                       const ::peleus_demo::mysql::syn::ServiceRequest* request,
                       ::peleus_demo::mysql::syn::ServiceResponse* response,
                       ::google::protobuf::Closure* done) override;
private:
    void parse_res(MYSQL_RES* res, std::string& response_str);
public:
    virtual void on_init(const char* conf_path) final;
    virtual void reset() final;
};

}
}
}
}

#endif //  PELEUS_MYSQL_SYN_SERVER_SRC_SERVICE_H
