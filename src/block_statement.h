#pragma once

#include <bits/stdc++.h>
#include "block.h"
#include "statement.h"

class BlockStatement : public Statement{
private:
    Block* block;
public:
    BlockStatement(Block *);
    ~BlockStatement();
};