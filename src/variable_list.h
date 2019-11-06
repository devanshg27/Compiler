#pragma once

#include <bits/stdc++.h>
#include "variable.h"

class AbstractDispatcher;

class Variable_list {
private:
    std::vector<Multivar_decl*> decls;
public:
    Variable_list();
    void Accept(AbstractDispatcher& dispatcher);
    void add_multivar_decl(Multivar_decl*);
    ~Variable_list();
};
