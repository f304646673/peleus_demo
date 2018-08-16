/*************************************************************************
    > File Name: main.cpp
    > Author: fangliang
    > Mail: f304646673@gmail.com 
    > Created Time: Fri 23 Mar 2018 07:52:34 PM CST
 ************************************************************************/
#include "entrance/repertory.h"
#include "main_server.h"
#include "inter_service.h"

using ::peleus::entrance::register_class;
using ::peleus_demo::server::NewInterServiceDemo;
using ::peleus_demo::server::InterService;

#define CHECK_BREAK(x)  \
    if (!(x)) {         \
        break;          \
    }                   \

#define REGMODULE(classname, name) \
    regist_suc = register_class<classname>(name);   \
    CHECK_BREAK(regist_suc)                         \

extern "C" {
    bool demo_main();
};

bool demo_main() {
    do {
        bool regist_suc = false;
        REGMODULE(NewInterServiceDemo, "NewInterServiceDemo");
        REGMODULE(InterService, "InterService");
    } while (0);
    return true;
}
