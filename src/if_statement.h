#pragma once

#include <bits/stdc++.h>
#include "block.h"
#include "expression.h"

class AbstractDispatcher;

class If_statement : public Statement {
private:
    Expression* cond;
    Block* block;
    If_statement* else_statement;
public:
    If_statement(Expression*, Block*, If_statement*);
    void Accept(AbstractDispatcher& dispatcher) override;
    ~If_statement();
};