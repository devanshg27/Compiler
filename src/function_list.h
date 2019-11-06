#pragma once

#include <bits/stdc++.h>
#include "function_declaration.h"

class Function_list {
private:
    std::vector<Function_decl*> decls;
public:
    Function_list();
    void add_function_decl(Function_decl*);
    ~Function_list();
};
