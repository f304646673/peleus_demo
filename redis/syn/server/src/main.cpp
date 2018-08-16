/*************************************************************************
    > File Name: main.cpp
    > Author: fangliang
    > Mail: f304646673@gmail.com 
    > Created Time: Fri 23 Mar 2018 07:52:34 PM CST
 ************************************************************************/
#include "entrance/repertory.h"
#include "service.h"

using ::peleus::entrance::register_class;
using ::peleus_demo::server::Service;

#define CHECK_BREAK(x)  \
    if (!(x)) {         \
        break;          \
    }                   \

#define REGMODULE(classname, name) \
    regist_suc = register_class<classname>(name);   \
    CHECK_BREAK(regist_suc)                         \

extern "C" {
    bool redis_syn_server_plugin_main();
};

bool redis_syn_server_plugin_main() {
    do {
        bool regist_suc = false;
        REGMODULE(Service, "Service");
    } while (0);
    return true;
}
