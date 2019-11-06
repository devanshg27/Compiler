#include "compound_expression.h"
#include "function_call.h"

ExpressionLiteral::ExpressionLiteral(Literal* _expr) : expr(_expr) {}
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
ExpressionIdentifier::~ExpressionIdentifier() {
    if (posx != NULL)
        delete posx;
    if (posy != NULL)
        delete posy;
}

Binary_op::Binary_op(Expression* _exp1, std::string _op, Expression* _exp2) : exp1(_exp1), op(_op), exp2(_exp2) {}
Binary_op::~Binary_op() {
    delete exp1;
    delete exp2;
}

Unary_op::Unary_op(std::string _op, Expression* _expr) : expr(_expr), op(_op){}
Unary_op::~Unary_op() {
    delete expr;
}

Ternary_op::Ternary_op(Expression* _cond, Expression* _exp1, Expression* _exp2) : exp1(_exp1), cond(_cond), exp2(_exp2) {}
Ternary_op::~Ternary_op() {
    delete cond;
    delete exp1;
    delete exp2;
}

ExpressionFunctionCall::ExpressionFunctionCall(Function_call* _fcall) : fcall(_fcall) {}
ExpressionFunctionCall::~ExpressionFunctionCall() { delete fcall; }

ExpressionBracketed::ExpressionBracketed(Expression* _expr) : expr(_expr) {}
ExpressionBracketed::~ExpressionBracketed() { delete expr; }