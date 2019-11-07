#pragma once

#include <bits/stdc++.h>
#include "function_call.h"
#include "statement.h"

class AbstractDispatcher;

class Function_call_statement : public Statement{
public:
    Function_call* fcall;
    Function_call_statement(Function_call *);
    void Accept(AbstractDispatcher& dispatcher) override;
    ~Function_call_statement();
};