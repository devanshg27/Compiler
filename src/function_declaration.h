#pragma once

#include <bits/stdc++.h>
#include "variable.h"
#include "block.h"

class AbstractDispatcher;

class Argument_list {
public:
    std::deque<Var_decl*> arguments;
    Argument_list();
    void add_argument(Var_decl*);
    void Accept(AbstractDispatcher& dispatcher);
    ~Argument_list();
};

class Function_decl {
public:
    std::string type, id;
    Argument_list* a_list;
    Block* blk;
    Function_decl(std::string, std::string, Argument_list*, Block*);
    void Accept(AbstractDispatcher& dispatcher);
    ~Function_decl();
};