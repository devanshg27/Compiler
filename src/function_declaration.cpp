#include "function_declaration.h"

Argument_list::Argument_list() {}

void Argument_list::add_argument(Var_decl* arg) {
    arguments.push_back(arg);
}

Argument_list::~Argument_list() {
    for(auto&z: arguments) {
        delete z;
    }
}

Function_decl::Function_decl(std::string _type, std::string _id, Argument_list* _a_list, Block* _blk) : type(_type), id(_id), a_list(_a_list), blk(_blk) {}
Function_decl::~Function_decl() {
    delete a_list;
    delete blk;
}
