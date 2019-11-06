#pragma once

#include <bits/stdc++.h>
#include "statement.h"

class AbstractDispatcher;

class Statement_list {
private:
    std::vector<Statement*> statements;
public:
    Statement_list();
    void Accept(AbstractDispatcher& dispatcher);
    void add_statement(Statement*);
    ~Statement_list();
};
