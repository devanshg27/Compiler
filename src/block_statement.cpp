#include "block_statement.h"

BlockStatement::BlockStatement(Block *_block) : block(_block) {}
BlockStatement::~BlockStatement() { delete block; }