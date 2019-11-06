#pragma once

#include <bits/stdc++.h>
#include "block.h"
#include "statement.h"

class AbstractDispatcher;

class BlockStatement : public Statement{
private:
    Block* block;
public:
    BlockStatement(Block *);
    void Accept(AbstractDispatcher& dispatcher) override;
    ~BlockStatement();
};