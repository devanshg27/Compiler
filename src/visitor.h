#pragma once

#include "node.h"

class AbstractDispatcher {  // Declares the interface for the dispatcher
public:
    // Declare overloads for each kind of node to dispatch
    virtual void Dispatch(Argument_list&) = 0;
    virtual void Dispatch(Assignment_statement&) = 0;
    virtual void Dispatch(Binary_op&) = 0;
    virtual void Dispatch(Block&) = 0;
    virtual void Dispatch(BlockStatement&) = 0;
    virtual void Dispatch(BooleanLiteral&) = 0;
    virtual void Dispatch(CharacterLiteral&) = 0;
    virtual void Dispatch(ExpressionBracketed&) = 0;
    virtual void Dispatch(ExpressionFunctionCall&) = 0;
    virtual void Dispatch(ExpressionIdentifier&) = 0;
    virtual void Dispatch(ExpressionLiteral&) = 0;
    virtual void Dispatch(For_statement&) = 0;
    virtual void Dispatch(Function_call&) = 0;
    virtual void Dispatch(Function_call_statement&) = 0;
    virtual void Dispatch(Function_decl&) = 0;
    virtual void Dispatch(Function_list&) = 0;
    virtual void Dispatch(If_statement&) = 0;
    virtual void Dispatch(IntegerLiteral&) = 0;
    virtual void Dispatch(Multivar_decl&) = 0;
    virtual void Dispatch(Parameter_list&) = 0;
    virtual void Dispatch(Program&) = 0;
    virtual void Dispatch(Return_statement&) = 0;
    virtual void Dispatch(Statement_list&) = 0;
    virtual void Dispatch(StringLiteral&) = 0;
    virtual void Dispatch(Ternary_op&) = 0;
    virtual void Dispatch(Unary_op&) = 0;
    virtual void Dispatch(Var_decl&) = 0;
    virtual void Dispatch(Variable_list&) = 0;
    virtual void Dispatch(While_statement&) = 0;
};