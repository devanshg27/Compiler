#pragma once

#include <bits/stdc++.h>
#include <variant>
#include "dispatcher_semantic_check.h"
#include "visitor.h"
#include "context.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Constant.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/GlobalVariable.h"

ostream& operator<<(ostream& s, const pair<string,vector<int>>& p);

class Dispatcher_llvm_gen : public AbstractDispatcher {
private:
    static const int _cpl_int_width = 32;
    static const int _cpl_char_width = 8;
    static const int _cpl_bool_width = 1;
    static const int _cpl_success = 1;

    llvm::LLVMContext the_context;
    llvm::IRBuilder<> *builder;
    llvm::Module* the_module;
    ContextNoError<std::string, llvm::AllocaInst*> named_values;
    Context<std::string, int> arr_sz;
    Context<std::string, int> var_type;
    Context<std::string, int> func_type;
    bool isGlobal;
    int curType;
    bool hasReturn;
public:
    llvm::Value *ret;

    Dispatcher_llvm_gen();

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

    void codeout();
    void codeout(std::string);
    llvm::AllocaInst *create_entry_alloc(llvm::Function*, std::string, int);
};