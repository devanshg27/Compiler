#pragma once

#include <bits/stdc++.h>
#include "expression.h"

class AbstractDispatcher;

class Parameter_list {
private:
    std::vector<Expression*> parameters;
public:
    Parameter_list();
    void add_parameter(Expression*);
    void Accept(AbstractDispatcher& dispatcher);
    ~Parameter_list();
};

class Function_call {
private:
    std::string id;
    Parameter_list* p_list;
public:
    Function_call(std::string, Parameter_list*);
    void Accept(AbstractDispatcher& dispatcher);
    ~Function_call();
};