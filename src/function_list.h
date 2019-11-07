#pragma once

#include <bits/stdc++.h>
#include "function_declaration.h"

class AbstractDispatcher;

class Function_list {
public:
    std::deque<Function_decl*> decls;
    Function_list();
    void add_function_decl(Function_decl*);
    void Accept(AbstractDispatcher& dispatcher);
    ~Function_list();
};
