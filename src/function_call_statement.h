#pragma once

#include <bits/stdc++.h>
#include "function_call.h"
#include "statement.h"

class Function_call_statement : public Statement{
private:
    Function_call* fcall;
public:
    Function_call_statement(Function_call *);
    ~Function_call_statement();
};