#pragma once

#include "visitor.h"

class Dispatcher_pretty_print : public AbstractDispatcher {
private:
    int tabs = 0;
    bool isFor = false;
public:
    // Declare overloads for each kind of node to dispatch
    void Dispatch(Argument_list&);
    void Dispatch(Assignment_statement&);
    void Dispatch(Binary_op&);
    void Dispatch(Block&);
    void Dispatch(BlockStatement&);
    void Dispatch(BooleanLiteral&);
    void Dispatch(CharacterLiteral&);
    void Dispatch(ExpressionBracketed&);
    void Dispatch(ExpressionFunctionCall&);
    void Dispatch(ExpressionIdentifier&);
    void Dispatch(ExpressionLiteral&);
    void Dispatch(For_statement&);
    void Dispatch(Function_call&);
    void Dispatch(Function_call_statement&);
    void Dispatch(Function_decl&);
    void Dispatch(Function_list&);
    void Dispatch(If_statement&);
    void Dispatch(IntegerLiteral&);
    void Dispatch(Multivar_decl&);
    void Dispatch(Parameter_list&);
    void Dispatch(Program&);
    void Dispatch(Return_statement&);
    void Dispatch(Statement_list&);
    void Dispatch(StringLiteral&);
    void Dispatch(Ternary_op&);
    void Dispatch(Unary_op&);
    void Dispatch(Var_decl&);
    void Dispatch(Variable_list&);
    void Dispatch(While_statement&);
};