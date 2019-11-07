#pragma once

#include <bits/stdc++.h>
#include "expression.h"

class AbstractDispatcher;

class Statement {
public:
    Statement();
    virtual void Accept(AbstractDispatcher& dispatcher) = 0;
    ~Statement();
};

class Assignment_statement : public Statement {
public:
    std::string id;
    Expression *posx;
    Expression *posy;
    Expression* expr;
    Assignment_statement(std::string, Expression*);
    Assignment_statement(std::string, Expression*, Expression*);
    Assignment_statement(std::string, Expression*, Expression*, Expression*);
    void Accept(AbstractDispatcher& dispatcher) override;
    ~Assignment_statement();
};

class Return_statement : public Statement {
public:
    Expression* expr;
    Return_statement(Expression*);
    void Accept(AbstractDispatcher& dispatcher) override;
    ~Return_statement();
};