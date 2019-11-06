#include "statement.h"

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
Assignment_statement::~Assignment_statement() {
    if (posx != NULL)
        delete posx;
    if (posy != NULL)
        delete posy;
}

Return_statement::Return_statement(Expression* _expr) : expr(_expr) {}
Return_statement::~Return_statement() { delete expr; }