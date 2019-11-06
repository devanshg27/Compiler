#pragma once

#include <bits/stdc++.h>
#include "variable_list.h"
#include "statement_list.h"

class AbstractDispatcher;

class Block {
private:
    Variable_list *v_list;
    Statement_list *s_list;
public:
    Block(Variable_list*, Statement_list*);
    void Accept(AbstractDispatcher& dispatcher);
    ~Block();
};
