#pragma once

#include <bits/stdc++.h>
#include "expression.h"

class Var_decl {
private:
    std::string type, id;
    int *shapex;
    int *shapey;
    Expression *initial_value;
public:
    Var_decl(std::string, std::string, Expression *);
    Var_decl(std::string, std::string, int, Expression *);
    Var_decl(std::string, std::string, int, int, Expression *);
    std::string getType();
    ~Var_decl();
};

class Multivar_decl {
private:
    std::vector<Var_decl*> decls;
public:
    Multivar_decl(Var_decl*);
    void add_var_decl(std::string, Expression*);
    void add_var_decl(std::string, int, Expression*);
    void add_var_decl(std::string, int, int, Expression*);
    ~Multivar_decl();
};