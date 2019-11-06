#pragma once

#include <bits/stdc++.h>
#include "variable.h"

class Variable_list {
private:
    std::vector<Multivar_decl*> decls;
public:
    Variable_list();
    void add_multivar_decl(Multivar_decl*);
    ~Variable_list();
};
