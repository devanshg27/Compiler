#pragma once

#include <bits/stdc++.h>
#include "statement.h"

class AbstractDispatcher;

class Statement_list {
public:
    std::deque<Statement*> statements;
    Statement_list();
    void Accept(AbstractDispatcher& dispatcher);
    void add_statement(Statement*);
    ~Statement_list();
};
