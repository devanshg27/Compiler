#include "function_list.h"

Function_list::Function_list() {}

void Function_list::add_function_decl(Function_decl* decl) {
    decls.push_back(decl);
}

Function_list::~Function_list() {
    for(auto&z: decls) {
        delete z;
    }
}