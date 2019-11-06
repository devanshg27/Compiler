#include "loops.h"
#include "visitor.h"

For_statement::For_statement(Multivar_decl* _decls, Expression* _cond, Statement* _upd, Block* _block) : decls(_decls), cond(_cond), upd(_upd), block(_block) {}
void For_statement::Accept(AbstractDispatcher& dispatcher) {
    dispatcher.Dispatch(*this);
}
For_statement::~For_statement() {
    if(decls != NULL) {
        delete decls;
    }
    if(cond != NULL) {
        delete cond;
    }
    if(upd != NULL) {
        delete upd;
    }
    if(block != NULL) {
        delete block;
    }
}

While_statement::While_statement(Expression* _cond, Block* _block) : cond(_cond), block(_block) {}
void While_statement::Accept(AbstractDispatcher& dispatcher) {
    dispatcher.Dispatch(*this);
}
While_statement::~While_statement() {
    delete cond;
    delete block;
}
