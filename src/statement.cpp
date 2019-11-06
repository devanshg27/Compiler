#include "statement.h"
#include "visitor.h"

Statement::Statement() {}
Statement::~Statement() {}

Assignment_statement::Assignment_statement(std::string _id, Expression* _expr) : id(_id), expr(_expr) {
    posx = NULL;
    posy = NULL;
}
Assignment_statement::Assignment_statement(std::string _id, Expression* _posx, Expression* _expr) : id(_id), expr(_expr) {
    posx = _posx;
    posy = NULL;
}
Assignment_statement::Assignment_statement(std::string _id, Expression* _posx, Expression* _posy, Expression* _expr) : id(_id), expr(_expr) {
    posx = _posx;
    posy = _posy;
}
void Assignment_statement::Accept(AbstractDispatcher& dispatcher) {
    dispatcher.Dispatch(*this);
}
Assignment_statement::~Assignment_statement() {
    if (posx != NULL)
        delete posx;
    if (posy != NULL)
        delete posy;
}

Return_statement::Return_statement(Expression* _expr) : expr(_expr) {}
void Return_statement::Accept(AbstractDispatcher& dispatcher) {
    dispatcher.Dispatch(*this);
}
Return_statement::~Return_statement() { delete expr; }