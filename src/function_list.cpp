#include "function_list.h"
#include "visitor.h"

Function_list::Function_list() {}

void Function_list::add_function_decl(Function_decl* decl) {
    decls.push_front(decl);
}
void Function_list::Accept(AbstractDispatcher& dispatcher) {
    dispatcher.Dispatch(*this);
}
Function_list::~Function_list() {
    for(auto&z: decls) {
        delete z;
    }
}