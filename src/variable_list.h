#pragma once

#include <bits/stdc++.h>
#include "variable.h"

class AbstractDispatcher;

class Variable_list {
public:
    std::vector<Multivar_decl*> decls;
    Variable_list();
    void Accept(AbstractDispatcher& dispatcher);
    void add_multivar_decl(Multivar_decl*);
    ~Variable_list();
};
