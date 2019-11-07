#pragma once

#include <bits/stdc++.h>
#include "expression.h"

class AbstractDispatcher;

class Parameter_list {
public:
    std::deque<Expression*> parameters;
    Parameter_list();
    void add_parameter(Expression*);
    void Accept(AbstractDispatcher& dispatcher);
    ~Parameter_list();
};

class Function_call {
public:
    std::string id;
    Parameter_list* p_list;
    Function_call(std::string, Parameter_list*);
    void Accept(AbstractDispatcher& dispatcher);
    ~Function_call();
};