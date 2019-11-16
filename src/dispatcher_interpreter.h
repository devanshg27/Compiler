#pragma once

#include <bits/stdc++.h>
#include <variant>
#include "visitor.h"
#include "context.h"
#include "container.h"

using ValueContainer = std::variant<Container<int>, Container<char>, Container<unsigned>, Container<bool>, string>;

class Dispatcher_interpreter : public AbstractDispatcher {
private:
    Context<ValueContainer> var_context;
    Context<Function_decl*> func_context;
    bool hasReturned = false;
    ValueContainer retval;
    ValueContainer func_retval;
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
    void Dispatch(UnsignedLiteral&);
    void Dispatch(Var_decl&);
    void Dispatch(Variable_list&);
    void Dispatch(While_statement&);
};