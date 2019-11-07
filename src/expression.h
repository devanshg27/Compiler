#pragma once

#include <bits/stdc++.h>

class AbstractDispatcher;

class Expression {
public:
    Expression();
    virtual void Accept(AbstractDispatcher& dispatcher) = 0;
    ~Expression();
};