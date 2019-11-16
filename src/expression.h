#pragma once

#include <bits/stdc++.h>

class AbstractDispatcher;

class Expression {
public:
    Expression();
    virtual void Accept(AbstractDispatcher& dispatcher) = 0;
    virtual std::pair<std::string,std::pair<Expression*,Expression*>>* getIdentifier() = 0;
    virtual ~Expression();
};