#include "if_statement.h"
#include "visitor.h"

If_statement::If_statement(Expression* _cond, Block* _block, If_statement* _else_statement) : cond(_cond), block(_block), else_statement(_else_statement) {}
void If_statement::Accept(AbstractDispatcher& dispatcher) {
    dispatcher.Dispatch(*this);
}
If_statement::~If_statement() {
    if(cond != NULL) delete cond;
    if(block != NULL) delete block;
    if(else_statement != NULL) delete else_statement;
}