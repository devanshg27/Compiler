#pragma once

#include <bits/stdc++.h>
#include "variable_list.h"
#include "function_list.h"

class AbstractDispatcher;

class Program {
public:
    Variable_list *v_list;
    Function_list *f_list;
    Program(Variable_list*, Function_list*);
    void Accept(AbstractDispatcher& dispatcher);
    ~Program();
};
