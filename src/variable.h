#pragma once

#include <bits/stdc++.h>
#include "expression.h"

class AbstractDispatcher;

class Var_decl {
public:
    std::string type, id;
    int *shapex;
    int *shapey;
    Expression *initial_value;
    Var_decl(std::string, std::string, Expression *);
    Var_decl(std::string, std::string, int, Expression *);
    Var_decl(std::string, std::string, int, int, Expression *);
    void Accept(AbstractDispatcher& dispatcher);
    std::string getType();
    ~Var_decl();
};

class Multivar_decl {
public:
    std::vector<Var_decl*> decls;
    Multivar_decl(Var_decl*);
    void add_var_decl(std::string, Expression*);
    void add_var_decl(std::string, int, Expression*);
    void add_var_decl(std::string, int, int, Expression*);
    void Accept(AbstractDispatcher& dispatcher);
    ~Multivar_decl();
};