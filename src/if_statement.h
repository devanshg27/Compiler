#pragma once

#include <bits/stdc++.h>
#include "block.h"
#include "expression.h"

class If_statement : public Statement {
private:
    Expression* cond;
    Block* block;
    If_statement* else_statement;
public:
    If_statement(Expression*, Block*, If_statement*);
    ~If_statement();
};