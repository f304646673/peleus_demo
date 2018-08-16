/*************************************************************************
    > File Name: main_server.h
    > Author: fangliang
    > Mail: f304646673@gmail.com 
    > Created Time: Tue 27 Mar 2018 12:11:40 PM CST
 ************************************************************************/
#ifndef PELEUS_MYSQL_ASYN_SERVER_MAIN_SERVER_H
#define PELEUS_MYSQL_ASYN_SERVER_MAIN_SERVER_H
#include "mysql/asyn/interface/asyn.pb.h"
#include "entrance/entrance.h"

namespace peleus_demo {
namespace mysql {
namespace asyn {
namespace server {

class MysqlAsyn : 
    public ::peleus_demo::mysql::asyn::MysqlAsynService,
    public ::peleus::entrance::Entrance
{
public:
    explicit MysqlAsyn(const char* name);

public:
  virtual void query(::google::protobuf::RpcController* controller,
                       const ::peleus_demo::mysql::asyn::MysqlAsynRequest* request,
                       ::peleus_demo::mysql::asyn::MysqlAsynResponse* response,
                       ::google::protobuf::Closure* done) override;
public:
    virtual void on_init(const char* conf_path) final;
    virtual void reset() final;
};

}
}
}
}

#endif //  PELEUS_MYSQL_ASYN_SERVER_MAIN_SERVER_H
