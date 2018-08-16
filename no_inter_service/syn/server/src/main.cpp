/*************************************************************************
    > File Name: main.cpp
    > Author: fangliang
    > Mail: f304646673@gmail.com 
    > Created Time: Fri 23 Mar 2018 07:52:34 PM CST
 ************************************************************************/
#include "entrance/repertory.h"
#include "main_server.h"

using ::peleus::entrance::register_class;
using ::peleus_demo::server::NoInterServiceDemo;

#define CHECK_BREAK(x)  \
    if (!(x)) {         \
        break;          \
    }                   \

#define REGMODULE(classname, name) \
    regist_suc = register_class<classname>(name);   \
    CHECK_BREAK(regist_suc)                         \

extern "C" {
    bool no_inter_service_syn_server_plugin_main();
};

bool no_inter_service_syn_server_plugin_main() {
    do {
        bool regist_suc = false;
        REGMODULE(NoInterServiceDemo, "NoInterServiceDemo");
    } while (0);
    return true;
}
