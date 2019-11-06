#pragma once

#include <bits/stdc++.h>
#include "variable.h"
#include "expression.h"
#include "statement.h"
#include "block.h"

class For_statement : public Statement {
private:
    Multivar_decl* decls;
    Expression* cond;
    Statement* upd;
    Block* block;
public:
    For_statement(Multivar_decl*, Expression*, Statement*, Block*);
    ~For_statement();
};

class While_statement : public Statement {
private:
    Expression* cond;
    Block* block;
public:
    While_statement(Expression*, Block*);
    ~While_statement();
};