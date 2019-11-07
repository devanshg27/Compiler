#pragma once

#include <bits/stdc++.h>
#include "block.h"
#include "expression.h"

class AbstractDispatcher;

class If_statement : public Statement {
public:
    Expression* cond;
    Block* block;
    If_statement* else_statement;
    If_statement(Expression*, Block*, If_statement*);
    void Accept(AbstractDispatcher& dispatcher) override;
    ~If_statement();
};