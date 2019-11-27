#pragma once

#include "visitor.h"
#include "context.h"

enum class Type{ INT, UNSIGNED, BOOL, CHAR, VOID, STRING};

ostream& operator<<(ostream& s, const pair<string,vector<Type>>& p);

class Dispatcher_semantic_check : public AbstractDispatcher {
private:
    Context<string, pair<Type, int>> var_context;
    Context<pair<string,vector<Type>>, Type> func_context;
    Type retval;
    Type cur_func_return_type;
    bool isGlobal;
    bool hasReturn;
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