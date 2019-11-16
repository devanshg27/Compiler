#include "compound_expression.h"
#include "function_call.h"
#include "visitor.h"

using namespace std;

ExpressionLiteral::ExpressionLiteral(Literal* _expr) : expr(_expr) {}
void ExpressionLiteral::Accept(AbstractDispatcher& dispatcher) {
    dispatcher.Dispatch(*this);
}
pair<string, pair<Expression*, Expression*>>* ExpressionLiteral::getIdentifier() {
    return NULL;
}
ExpressionLiteral::~ExpressionLiteral() { delete expr; }

ExpressionIdentifier::ExpressionIdentifier(std::string _id) : id(_id) {
    posx = NULL;
    posy = NULL;
}
ExpressionIdentifier::ExpressionIdentifier(std::string _id, Expression* _posx) : id(_id) {
    posx = _posx;
    posy = NULL;
}
ExpressionIdentifier::ExpressionIdentifier(std::string _id, Expression* _posx, Expression* _posy) : id(_id) {
    posx = _posx;
    posy = _posy;
}
void ExpressionIdentifier::Accept(AbstractDispatcher& dispatcher) {
    dispatcher.Dispatch(*this);
}
pair<string, pair<Expression*, Expression*>>* ExpressionIdentifier::getIdentifier() {
    pair<string, pair<Expression*, Expression*>>* y = new pair<string, pair<Expression*, Expression*>>();
    y->first = id;
    y->second.first = posx;
    y->second.second = posy;
    return y;
}
ExpressionIdentifier::~ExpressionIdentifier() {
    if (posx != NULL)
        delete posx;
    if (posy != NULL)
        delete posy;
}

Binary_op::Binary_op(Expression* _exp1, std::string _op, Expression* _exp2) : exp1(_exp1), op(_op), exp2(_exp2) {}
void Binary_op::Accept(AbstractDispatcher& dispatcher) {
    dispatcher.Dispatch(*this);
}
pair<string, pair<Expression*, Expression*>>* Binary_op::getIdentifier() {
    return NULL;
}
Binary_op::~Binary_op() {
    delete exp1;
    delete exp2;
}

Unary_op::Unary_op(std::string _op, Expression* _expr) : op(_op), expr(_expr) {}
void Unary_op::Accept(AbstractDispatcher& dispatcher) {
    dispatcher.Dispatch(*this);
}
pair<string, pair<Expression*, Expression*>>* Unary_op::getIdentifier() {
    return NULL;
}
Unary_op::~Unary_op() {
    delete expr;
}

Ternary_op::Ternary_op(Expression* _cond, Expression* _exp1, Expression* _exp2) : cond(_cond), exp1(_exp1), exp2(_exp2) {}
void Ternary_op::Accept(AbstractDispatcher& dispatcher) {
    dispatcher.Dispatch(*this);
}
pair<string, pair<Expression*, Expression*>>* Ternary_op::getIdentifier() {
    return NULL;
}
Ternary_op::~Ternary_op() {
    delete cond;
    delete exp1;
    delete exp2;
}

ExpressionFunctionCall::ExpressionFunctionCall(Function_call* _fcall) : fcall(_fcall) {}
void ExpressionFunctionCall::Accept(AbstractDispatcher& dispatcher) {
    dispatcher.Dispatch(*this);
}
pair<string, pair<Expression*, Expression*>>* ExpressionFunctionCall::getIdentifier() {
    return NULL;
}
ExpressionFunctionCall::~ExpressionFunctionCall() { delete fcall; }

ExpressionBracketed::ExpressionBracketed(Expression* _expr) : expr(_expr) {}
void ExpressionBracketed::Accept(AbstractDispatcher& dispatcher) {
    dispatcher.Dispatch(*this);
}
pair<string, pair<Expression*, Expression*>>* ExpressionBracketed::getIdentifier() {
    return NULL;
}
ExpressionBracketed::~ExpressionBracketed() { delete expr; }