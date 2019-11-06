#include "if_statement.h"

If_statement::If_statement(Expression* _cond, Block* _block, If_statement* _else_statement) : cond(_cond), block(_block), else_statement(_else_statement) {}
If_statement::~If_statement() {
    if(cond != NULL) delete cond;
    if(block != NULL) delete block;
    if(else_statement != NULL) delete else_statement;
}