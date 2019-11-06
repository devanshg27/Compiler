#include "variable_list.h"
#include "visitor.h"

Variable_list::Variable_list() {}

void Variable_list::Accept(AbstractDispatcher& dispatcher) {
    dispatcher.Dispatch(*this);
}

void Variable_list::add_multivar_decl(Multivar_decl* decl) {
    decls.push_back(decl);
}

Variable_list::~Variable_list() {
    for(auto&z: decls) {
        delete z;
    }
}