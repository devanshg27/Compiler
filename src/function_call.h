#pragma once

#include <bits/stdc++.h>
#include "expression.h"

class Parameter_list {
private:
    std::vector<Expression*> parameters;
public:
    Parameter_list();
    void add_parameter(Expression*);
    ~Parameter_list();
};

class Function_call {
private:
    std::string id;
    Parameter_list* p_list;
public:
    Function_call(std::string, Parameter_list*);
    ~Function_call();
};