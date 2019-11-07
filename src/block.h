#pragma once

#include <bits/stdc++.h>
#include "variable_list.h"
#include "statement_list.h"

class AbstractDispatcher;

class Block {
public:
    Variable_list *v_list;
    Statement_list *s_list;
    Block(Variable_list*, Statement_list*);
    void Accept(AbstractDispatcher& dispatcher);
    ~Block();
};
