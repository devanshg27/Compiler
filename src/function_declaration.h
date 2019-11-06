#pragma once

#include <bits/stdc++.h>
#include "variable.h"
#include "block.h"

class AbstractDispatcher;

class Argument_list {
private:
    std::vector<Var_decl*> arguments;
public:
    Argument_list();
    void add_argument(Var_decl*);
    void Accept(AbstractDispatcher& dispatcher);
    ~Argument_list();
};

class Function_decl {
private:
    std::string type, id;
    Argument_list* a_list;
    Block* blk;
public:
    Function_decl(std::string, std::string, Argument_list*, Block*);
    void Accept(AbstractDispatcher& dispatcher);
    ~Function_decl();
};