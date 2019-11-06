#include "block_statement.h"
#include "visitor.h"

BlockStatement::BlockStatement(Block *_block) : block(_block) {}

void BlockStatement::Accept(AbstractDispatcher& dispatcher) {
    dispatcher.Dispatch(*this);
}

BlockStatement::~BlockStatement() { delete block; }