#pragma once

#include <bits/stdc++.h>
#include "statement.h"

class Statement_list {
private:
    std::vector<Statement*> statements;
public:
    Statement_list();
    void add_statement(Statement*);
    ~Statement_list();
};
