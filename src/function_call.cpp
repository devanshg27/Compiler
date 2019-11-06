#include "function_call.h"
#include "expression.h"

Parameter_list::Parameter_list() {}

void Parameter_list::add_parameter(Expression* p) {
    parameters.push_back(p);
}

Parameter_list::~Parameter_list() {
    for(auto&z: parameters) {
        delete z;
    }
}

Function_call::Function_call(std::string _id, Parameter_list* _p_list) : id(_id), p_list(_p_list) {}
Function_call::~Function_call() { delete p_list; }
