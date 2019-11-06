#pragma once

#include <bits/stdc++.h>
#include "function_call.h"
#include "statement.h"

class AbstractDispatcher;

class Function_call_statement : public Statement{
private:
    Function_call* fcall;
public:
    Function_call_statement(Function_call *);
    void Accept(AbstractDispatcher& dispatcher) override;
    ~Function_call_statement();
};