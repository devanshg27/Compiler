#pragma once

#include <bits/stdc++.h>
#include "expression.h"

class Statement {
private:
public:
    Statement();
    ~Statement();
};

class Assignment_statement : public Statement {
private:
    std::string id;
    Expression *posx;
    Expression *posy;
    Expression* expr;
public:
    Assignment_statement(std::string, Expression*);
    Assignment_statement(std::string, Expression*, Expression*);
    Assignment_statement(std::string, Expression*, Expression*, Expression*);
    ~Assignment_statement();
};

class Return_statement : public Statement {
private:
    Expression* expr;
public:
    Return_statement(Expression*);
    ~Return_statement();
};