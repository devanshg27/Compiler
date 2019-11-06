#include "statement_list.h"
#include "visitor.h"

Statement_list::Statement_list() {}

void Statement_list::Accept(AbstractDispatcher& dispatcher) {
    dispatcher.Dispatch(*this);
}

void Statement_list::add_statement(Statement* s) {
    statements.push_back(s);
}

Statement_list::~Statement_list() {
    for(auto&z: statements) {
        delete z;
    }
}