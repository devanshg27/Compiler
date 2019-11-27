#include <bits/stdc++.h>
#include "dispatcher_llvm_gen.h"

using namespace std;

const map<string,int> typeMap = {
    {"void", -1},
    {"int", 0},
    {"char", 1},
    {"unsigned", 2},
    {"bool", 3},
    {"string", 4}
};

Dispatcher_llvm_gen::Dispatcher_llvm_gen() {
    builder = new llvm::IRBuilder<>(the_context);
    the_module = new llvm::Module("cpl_prog", the_context);
}

void Dispatcher_llvm_gen::codeout() {
    the_module->print(llvm::outs(), nullptr);
    return;
}

void Dispatcher_llvm_gen::codeout(std::string fname) {
    std::error_code EC;
    llvm::raw_fd_ostream *out = new llvm::raw_fd_ostream(fname, EC);
    the_module->print(*out, nullptr);
    return;
}

llvm::AllocaInst* Dispatcher_llvm_gen::create_entry_alloc(llvm::Function *func, std::string var_name, int typ) {
    /* Get the builder for current context */
    llvm::IRBuilder<> tmp(&func->getEntryBlock(), func->getEntryBlock().begin());
    llvm::AllocaInst *alloca_instruction = nullptr;
    if (typ == 0 || typ == 2) {
        alloca_instruction = tmp.CreateAlloca(llvm::Type::getInt32Ty(the_context), 0, var_name);
    } else if (typ == 3) {
        alloca_instruction = tmp.CreateAlloca(llvm::Type::getInt1Ty(the_context), 0, var_name);
    } else if (typ == 1) {
        alloca_instruction = tmp.CreateAlloca(llvm::Type::getInt8Ty(the_context), 0, var_name);
    }
    return alloca_instruction;
}

void Dispatcher_llvm_gen::Dispatch(Argument_list& z) {
    assert(0);
}
void Dispatcher_llvm_gen::Dispatch(Assignment_statement& z) {
    int cnt = 0;
    llvm::Value *pos_x = nullptr, *pos_y = nullptr;
    if(z.posx) {
        z.posx->Accept(*this);
        pos_x = ret;
        ++cnt;
    }
    if(z.posy) {
        z.posy->Accept(*this);
        pos_y = ret;
        ++cnt;
    }
    z.expr->Accept(*this);
    llvm::Value* val = ret;
    llvm::Value* lloc = nullptr;
    lloc = named_values.get_value(z.id, nullptr);
    if(!lloc) lloc = the_module->getNamedGlobal(z.id);
    if(!lloc) assert(0);
    if(cnt==1) {
        llvm::Value* index = pos_x;
        assert(index);
        std::vector<llvm::Value*> array_idx;
        array_idx.emplace_back(builder->getInt32(0));
        array_idx.emplace_back(index);
        lloc = builder->CreateGEP(lloc, array_idx, z.id + "_idx");
    }
    if(cnt==2) {
        llvm::Value* index = pos_x;
        assert(index);
        llvm::Value* sz1 = llvm::ConstantInt::get(the_context, llvm::APInt(_cpl_int_width, arr_sz.get_value(z.id)));
        index = builder->CreateMul(sz1, index, "mul_tmp");
        assert(index);
        index = builder->CreateAdd(pos_y, index, "add_tmp");
        assert(index);
        std::vector<llvm::Value*> array_idx;
        array_idx.emplace_back(builder->getInt32(0));
        array_idx.emplace_back(index);
        lloc = builder->CreateGEP(lloc, array_idx, z.id + "_idx");
    }
    ret = builder->CreateStore(val, lloc);
}
void Dispatcher_llvm_gen::Dispatch(Binary_op& z) {
    z.exp1->Accept(*this);
    llvm::Value* left_op = ret;
    z.exp2->Accept(*this);
    llvm::Value* right_op = ret;
    assert(left_op and right_op);
    if(z.op == "+") {
        ret = builder->CreateAdd(left_op, right_op, "add_tmp");
    }
    else if(z.op == "-") {
        ret = builder->CreateSub(left_op, right_op, "sub_tmp");
    }
    else if(z.op == "*") {
        ret = builder->CreateMul(left_op, right_op, "mul_tmp");
    }
    else if(z.op == "/") {
        if(curType == 0) ret = builder->CreateSDiv(left_op, right_op, "div_tmp");
        else if(curType == 2) ret = builder->CreateUDiv(left_op, right_op, "div_tmp");
        else assert(0);
    }
    else if(z.op == "%") {
        if(curType == 0) ret = builder->CreateSRem(left_op, right_op, "mod_tmp");
        else if(curType == 2) ret = builder->CreateURem(left_op, right_op, "mod_tmp");
        else assert(0);
    }
    else if(z.op == "or") {
        ret = builder->CreateOr(left_op, right_op, "lor_tmp");
    }
    else if(z.op == "and") {
        ret = builder->CreateAnd(left_op, right_op, "lad_tmp");
    }
    else if(z.op == "xor") {
        ret = builder->CreateXor(left_op, right_op, "lxr_tmp");
    }
    else if(z.op == "<") {
        if(curType == 0) ret = builder->CreateICmpSLT(left_op, right_op, "les_tmp");
        else if(curType == 2) ret = builder->CreateICmpULT(left_op, right_op, "les_tmp");
        else assert(0);
    }
    else if(z.op == ">") {
        if(curType == 0) ret = builder->CreateICmpSGT(left_op, right_op, "gre_tmp");
        else if(curType == 2) ret = builder->CreateICmpUGT(left_op, right_op, "gre_tmp");
        else assert(0);
    }
    else if(z.op == "<=") {
        if(curType == 0) ret = builder->CreateICmpSLE(left_op, right_op, "leq_tmp");
        else if(curType == 2) ret = builder->CreateICmpULE(left_op, right_op, "leq_tmp");
        else assert(0);
    }
    else if(z.op == ">=") {
        if(curType == 0) ret = builder->CreateICmpSGE(left_op, right_op, "geq_tmp");
        else if(curType == 2) ret = builder->CreateICmpUGE(left_op, right_op, "geq_tmp");
        else assert(0);
    }
    else if(z.op == "==") {
        ret = builder->CreateICmpEQ(left_op, right_op, "eql_tmp");
    }
    else if(z.op == "!=") {
        ret = builder->CreateICmpNE(left_op, right_op, "neq_tmp");
    }
    else{
        assert(0);
    }
}
void Dispatcher_llvm_gen::Dispatch(Block& z) {
    int oldsz = named_values.get_context_size();
    int oldsz2 = var_type.get_context_size();
    z.v_list->Accept(*this);
    z.s_list->Accept(*this);
    named_values.resize_context(oldsz);
    var_type.resize_context(oldsz2);
}
void Dispatcher_llvm_gen::Dispatch(BlockStatement& z) {
    z.block->Accept(*this);
}
void Dispatcher_llvm_gen::Dispatch(BooleanLiteral& z) {
    curType = 3;
    ret = llvm::ConstantInt::get(the_context, llvm::APInt(_cpl_bool_width, z.val));
}
void Dispatcher_llvm_gen::Dispatch(CharacterLiteral& z) {
    curType = 1;
    ret = llvm::ConstantInt::get(the_context, llvm::APInt(_cpl_char_width, z.val));
}
void Dispatcher_llvm_gen::Dispatch(ExpressionBracketed& z) {
    z.expr->Accept(*this);
}
void Dispatcher_llvm_gen::Dispatch(ExpressionFunctionCall& z) {
    z.fcall->Accept(*this);
}
void Dispatcher_llvm_gen::Dispatch(ExpressionIdentifier& z) {
    int cnt = 0;
    llvm::Value *pos_x, *pos_y;
    if(z.posx) {
        z.posx->Accept(*this);
        pos_x = ret;
        ++cnt;
    }
    if(z.posy) {
        z.posy->Accept(*this);
        pos_y = ret;
        ++cnt;
    }
    llvm::Value* lloc = nullptr;
    lloc = named_values.get_value(z.id, nullptr);
    if(!lloc) lloc = the_module->getNamedGlobal(z.id);
    if(!lloc) assert(0);
    if(cnt==1) {
        llvm::Value* index = pos_x;
        assert(index);
        std::vector<llvm::Value*> array_idx;
        array_idx.emplace_back(builder->getInt32(0));
        array_idx.emplace_back(index);
        lloc = builder->CreateGEP(lloc, array_idx, z.id + "_idx");
    }
    if(cnt==2) {
        llvm::Value* index = pos_x;
        assert(index);
        llvm::Value* sz1 = llvm::ConstantInt::get(the_context, llvm::APInt(_cpl_int_width, arr_sz.get_value(z.id)));
        index = builder->CreateMul(sz1, index, "mul_tmp");
        assert(index);
        index = builder->CreateAdd(pos_y, index, "add_tmp");
        assert(index);
        std::vector<llvm::Value*> array_idx;
        array_idx.emplace_back(builder->getInt32(0));
        array_idx.emplace_back(index);
        lloc = builder->CreateGEP(lloc, array_idx, z.id + "_idx");
    }
    ret = builder->CreateLoad(lloc);
    curType = var_type.get_value(z.id);
}
void Dispatcher_llvm_gen::Dispatch(ExpressionLiteral& z) {
    z.expr->Accept(*this);
}
void Dispatcher_llvm_gen::Dispatch(For_statement& z) {
    llvm::Function *TheFunction = builder->GetInsertBlock()->getParent();

    int oldsz = named_values.get_context_size();
    int oldsz2 = var_type.get_context_size();
    z.decls->Accept(*this);

    llvm::BasicBlock *LoopBB = llvm::BasicBlock::Create(the_context, "loop", TheFunction);

    llvm::BasicBlock *AfterBB =
        llvm::BasicBlock::Create(the_context, "afterloop", TheFunction);

    z.cond->Accept(*this);
    llvm::Value *StartCond = ret;
    if (!StartCond) assert(0);
    builder->CreateCondBr(StartCond, LoopBB, AfterBB);

    builder->SetInsertPoint(LoopBB);

    z.block->Accept(*this);
    assert(ret);

    z.upd->Accept(*this);

    z.cond->Accept(*this);
    llvm::Value *EndCond = ret;
    if (!EndCond) assert(0);

    builder->CreateCondBr(EndCond, LoopBB, AfterBB);

    builder->SetInsertPoint(AfterBB);

    named_values.resize_context(oldsz);
    var_type.resize_context(oldsz2);

    ret = llvm::ConstantInt::get(the_context, llvm::APInt(_cpl_int_width, _cpl_success));
    hasReturn = false;
}
void Dispatcher_llvm_gen::Dispatch(Function_call& z) {
    if(z.id == "print") {
        for(auto&p: z.p_list->parameters) {
            p->Accept(*this);
            if(curType == 0) {
                llvm::Value* arg_val = nullptr;
                std::vector<llvm::Type*> arg_types;
                std::vector<llvm::Value*> arg_vals;
                arg_val = builder->CreateGlobalStringPtr("%d");
                arg_vals.push_back(arg_val);
                arg_types.push_back(arg_val->getType());
                arg_vals.push_back(ret);
                arg_types.push_back(ret->getType());
                llvm::FunctionType* func_type = llvm::FunctionType::get(llvm::Type::getInt32Ty(the_context), arg_types, false);
                llvm::Constant* func = the_module->getOrInsertFunction("printf", func_type);
                if(!func) assert(0);
                ret = builder->CreateCall(func, arg_vals);
            }
            else if(curType == 1) {
                llvm::Value* arg_val = nullptr;
                std::vector<llvm::Type*> arg_types;
                std::vector<llvm::Value*> arg_vals;
                arg_val = builder->CreateGlobalStringPtr("%c");
                arg_vals.push_back(arg_val);
                arg_types.push_back(arg_val->getType());
                arg_vals.push_back(ret);
                arg_types.push_back(ret->getType());
                llvm::FunctionType* func_type = llvm::FunctionType::get(llvm::Type::getInt32Ty(the_context), arg_types, false);
                llvm::Constant* func = the_module->getOrInsertFunction("printf", func_type);
                if(!func) assert(0);
                ret = builder->CreateCall(func, arg_vals);
            }
            else if(curType == 2) {
                llvm::Value* arg_val = nullptr;
                std::vector<llvm::Type*> arg_types;
                std::vector<llvm::Value*> arg_vals;
                arg_val = builder->CreateGlobalStringPtr("%u");
                arg_vals.push_back(arg_val);
                arg_types.push_back(arg_val->getType());
                arg_vals.push_back(ret);
                arg_types.push_back(ret->getType());
                llvm::FunctionType* func_type = llvm::FunctionType::get(llvm::Type::getInt32Ty(the_context), arg_types, false);
                llvm::Constant* func = the_module->getOrInsertFunction("printf", func_type);
                if(!func) assert(0);
                ret = builder->CreateCall(func, arg_vals);
            }
            else if(curType == 3) {
                assert(0);
            }
            else if(curType == 4) {
                llvm::Value* arg_val = nullptr;
                std::vector<llvm::Type*> arg_types;
                std::vector<llvm::Value*> arg_vals;
                arg_val = builder->CreateGlobalStringPtr("%s");
                arg_vals.push_back(arg_val);
                arg_types.push_back(arg_val->getType());
                arg_vals.push_back(ret);
                arg_types.push_back(ret->getType());
                llvm::FunctionType* func_type = llvm::FunctionType::get(llvm::Type::getInt32Ty(the_context), arg_types, false);
                llvm::Constant* func = the_module->getOrInsertFunction("printf", func_type);
                if(!func) assert(0);
                ret = builder->CreateCall(func, arg_vals);
            }
            else assert(0);
        }
        return;
    }
    if(z.id == "read") {
        for(auto&p: z.p_list->parameters) {
            auto y = p->getIdentifier();
            int cnt = 0;
            llvm::Value *pos_x, *pos_y;
            if(y->second.first) {
                y->second.first->Accept(*this);
                pos_x = ret;
                ++cnt;
            }
            if(y->second.second) {
                y->second.second->Accept(*this);
                pos_y = ret;
                ++cnt;
            }
            llvm::Value* lloc = nullptr;
            lloc = named_values.get_value(y->first, nullptr);
            if(!lloc) lloc = the_module->getNamedGlobal(y->first);
            if(!lloc) assert(0);
            if(cnt==1) {
                assert(pos_x);
                std::vector<llvm::Value*> array_idx;
                array_idx.emplace_back(builder->getInt32(0));
                array_idx.emplace_back(pos_x);
                lloc = builder->CreateGEP(lloc, array_idx, y->first + "_idx");
            }
            if(cnt==2) {
                assert(pos_x);
                llvm::Value* sz1 = llvm::ConstantInt::get(the_context, llvm::APInt(_cpl_int_width, arr_sz.get_value(y->first)));
                llvm::Value* index = builder->CreateMul(sz1, pos_x, "mul_tmp");
                assert(index);
                index = builder->CreateAdd(pos_y, index, "add_tmp");
                assert(index);
                std::vector<llvm::Value*> array_idx;
                array_idx.emplace_back(builder->getInt32(0));
                array_idx.emplace_back(index);
                lloc = builder->CreateGEP(lloc, array_idx, y->first + "_idx");
            }
            if(var_type.get_value(y->first) == 0) {
                llvm::Value* arg_val = nullptr;
                std::vector<llvm::Type*> arg_types;
                std::vector<llvm::Value*> arg_vals;
                arg_val = builder->CreateGlobalStringPtr("%d");
                arg_vals.push_back(arg_val);
                arg_types.push_back(arg_val->getType());
                arg_vals.push_back(lloc);
                arg_types.push_back(lloc->getType());
                llvm::FunctionType* func_type = llvm::FunctionType::get(llvm::Type::getInt32Ty(the_context), arg_types, false);
                llvm::Constant* func = the_module->getOrInsertFunction("scanf", func_type);
                if(!func) assert(0);
                ret = builder->CreateCall(func, arg_vals);
            }
            if(var_type.get_value(y->first) == 1) {
                llvm::Value* arg_val = nullptr;
                std::vector<llvm::Type*> arg_types;
                std::vector<llvm::Value*> arg_vals;
                arg_val = builder->CreateGlobalStringPtr("%c");
                arg_vals.push_back(arg_val);
                arg_types.push_back(arg_val->getType());
                arg_vals.push_back(lloc);
                arg_types.push_back(lloc->getType());
                llvm::FunctionType* func_type = llvm::FunctionType::get(llvm::Type::getInt32Ty(the_context), arg_types, false);
                llvm::Constant* func = the_module->getOrInsertFunction("scanf", func_type);
                if(!func) assert(0);
                ret = builder->CreateCall(func, arg_vals);
            }
            if(var_type.get_value(y->first) == 2) {
                llvm::Value* arg_val = nullptr;
                std::vector<llvm::Type*> arg_types;
                std::vector<llvm::Value*> arg_vals;
                arg_val = builder->CreateGlobalStringPtr("%u");
                arg_vals.push_back(arg_val);
                arg_types.push_back(arg_val->getType());
                arg_vals.push_back(lloc);
                arg_types.push_back(lloc->getType());
                llvm::FunctionType* func_type = llvm::FunctionType::get(llvm::Type::getInt32Ty(the_context), arg_types, false);
                llvm::Constant* func = the_module->getOrInsertFunction("scanf", func_type);
                if(!func) assert(0);
                ret = builder->CreateCall(func, arg_vals);
            }
            if(var_type.get_value(y->first) == 3) {
                assert(0);
            }
            if(var_type.get_value(y->first) == 4) {
                assert(0);
            }
            delete y;
        }
        return;
    }

    llvm::Function* calleef = the_module->getFunction(z.id);

    if (!calleef) assert(0);

    std::vector <llvm::Value*> argsv;
    vector<int> types;
    for (int i = 0; i < (int)z.p_list->parameters.size(); ++i) {
        z.p_list->parameters[i]->Accept(*this);
        if(!ret) assert(0);
        argsv.push_back(ret);
        types.push_back(curType);
    }
    curType = func_type.get_value(z.id);
    if(curType == -1) ret = builder->CreateCall(calleef, argsv);
    else ret = builder->CreateCall(calleef, argsv, "cal_tmp");
}
void Dispatcher_llvm_gen::Dispatch(Function_call_statement& z) {
    z.fcall->Accept(*this);
}
void Dispatcher_llvm_gen::Dispatch(Function_decl& z) {
    func_type.add_context({z.id, typeMap.at(z.type)});
    vector<llvm::Type*> method_args;
    for(int i = 0; i < z.a_list->arguments.size(); ++i) {
        int arg_typ = typeMap.at(z.a_list->arguments[i]->type);
        string arg_name = z.a_list->arguments[i]->id;
        if(arg_typ == 0)
            method_args.emplace_back(llvm::Type::getInt32Ty(the_context));
        else if(arg_typ == 1)
            method_args.emplace_back(llvm::Type::getInt8Ty(the_context));
        else if(arg_typ == 3)
            method_args.emplace_back(llvm::Type::getInt32Ty(the_context));
        else if(arg_typ == 3)
            method_args.emplace_back(llvm::Type::getInt1Ty(the_context));
        else
            assert(0);
    }

    llvm::Type* ret_typ;
    if(typeMap.at(z.type) == 0)
        ret_typ = llvm::Type::getInt32Ty(the_context);
    else if(typeMap.at(z.type) == 1)
        ret_typ = llvm::Type::getInt8Ty(the_context);
    else if(typeMap.at(z.type) == 2)
        ret_typ = llvm::Type::getInt32Ty(the_context);
    else if(typeMap.at(z.type) == 3)
        ret_typ = llvm::Type::getInt1Ty(the_context);
    else if(typeMap.at(z.type) == -1)
        ret_typ = llvm::Type::getVoidTy(the_context);
    else
        assert(0);

    llvm::FunctionType* func_typ = llvm::FunctionType::get(ret_typ, method_args, false);
    llvm::Function *func = llvm::Function::Create(func_typ, llvm::Function::ExternalLinkage,
                                    z.id, the_module);
    int idx = 0;
    for(llvm::Function::arg_iterator itr = func->arg_begin(); itr != func->arg_end(); ++itr, ++idx)
        itr->setName(z.a_list->arguments[idx]->id);

    llvm::BasicBlock* func_blk = llvm::BasicBlock::Create(the_context, "entrypoint", func);
    builder->SetInsertPoint(func_blk);

    idx = 0;
    for(llvm::Function::arg_iterator itr = func->arg_begin(); itr != func->arg_end(); ++itr, ++idx) {
        llvm::AllocaInst *local_arg = create_entry_alloc(func, z.a_list->arguments[idx]->id, typeMap.at(z.a_list->arguments[idx]->type));
        builder->CreateStore(itr, local_arg);
        named_values.add_context(make_pair(z.a_list->arguments[idx]->id, local_arg));
        var_type.add_context(make_pair(z.a_list->arguments[idx]->id, typeMap.at(z.a_list->arguments[idx]->type)));
    }

    z.blk->Accept(*this);
    if(typeMap.at(z.type) != -1) {
        assert(hasReturn);
    }
    else if(!hasReturn) {
        builder->CreateRetVoid();
    }
    hasReturn = false;
    if(!ret) {
        func->eraseFromParent();
        assert(0);
    }
    verifyFunction(*func);
    vector<int> temp;
    for(auto&d: z.a_list->arguments) {
        temp.push_back(typeMap.at(d->getType()));
    }
}
void Dispatcher_llvm_gen::Dispatch(Function_list& z) {
    for(auto& y: z.decls) {
        y->Accept(*this);
        if(!ret) return;
    }
    ret = llvm::ConstantInt::get(the_context, llvm::APInt(_cpl_int_width, _cpl_success));
}
void Dispatcher_llvm_gen::Dispatch(If_statement& z) {
    if(z.cond) {
        z.cond->Accept(*this);
        llvm::Value *CondV = ret;
        if (!CondV) assert(0);

        llvm::Function *TheFunction = builder->GetInsertBlock()->getParent();

        llvm::BasicBlock *ThenBB = llvm::BasicBlock::Create(the_context, "then", TheFunction);
        llvm::BasicBlock *ElseBB = llvm::BasicBlock::Create(the_context, "else");
        llvm::BasicBlock *MergeBB = llvm::BasicBlock::Create(the_context, "ifcont");

        builder->CreateCondBr(CondV, ThenBB, ElseBB);

        builder->SetInsertPoint(ThenBB);

        bool _hasReturn = false;
        z.block->Accept(*this);
        if(hasReturn) _hasReturn = true;
        hasReturn = false;
        llvm::Value *ThenV = ret;
        if (!ThenV) assert(0);

        if(!_hasReturn) builder->CreateBr(MergeBB);
        ThenBB = builder->GetInsertBlock();

        TheFunction->getBasicBlockList().push_back(ElseBB);
        builder->SetInsertPoint(ElseBB);

        if(z.else_statement) z.else_statement->Accept(*this);
        bool else_return = hasReturn;
        if(hasReturn and _hasReturn) hasReturn = true;
        else hasReturn = false;
        llvm::Value *ElseV = ret;
        if (!ElseV)  assert(0);

        if(!else_return) builder->CreateBr(MergeBB);
        ElseBB = builder->GetInsertBlock();

        TheFunction->getBasicBlockList().push_back(MergeBB);
        builder->SetInsertPoint(MergeBB);
        if(hasReturn) {
            llvm::Type* ret_type = builder->GetInsertBlock()->getParent()->getReturnType();
            if(ret_type == llvm::Type::getInt32Ty(the_context)) builder->CreateRet(llvm::ConstantInt::get(the_context, llvm::APInt(_cpl_int_width, _cpl_success)));
            else if(ret_type == llvm::Type::getInt8Ty(the_context)) builder->CreateRet(llvm::ConstantInt::get(the_context, llvm::APInt(_cpl_char_width, _cpl_success)));
            else if(ret_type == llvm::Type::getInt1Ty(the_context)) builder->CreateRet(llvm::ConstantInt::get(the_context, llvm::APInt(_cpl_bool_width, _cpl_success)));
            else if(ret_type == llvm::Type::getVoidTy(the_context)) builder->CreateRetVoid();
            else assert(0);
        }
    }
    else {
        z.block->Accept(*this);
    }
}
void Dispatcher_llvm_gen::Dispatch(IntegerLiteral& z) {
    curType = 0;
    ret = llvm::ConstantInt::get(the_context, llvm::APInt(_cpl_int_width, z.val));
}
void Dispatcher_llvm_gen::Dispatch(Multivar_decl& z) {
    for(auto&y: z.decls) {
        y->Accept(*this);
        if(!ret) return;
    }
}
void Dispatcher_llvm_gen::Dispatch(Parameter_list& z) {
    assert(0);
}
void Dispatcher_llvm_gen::Dispatch(Program& z) {
    isGlobal = true;
    z.v_list->Accept(*this);
    if(!ret) return;
    isGlobal = false;
    z.f_list->Accept(*this);
    if(!ret) return;
    ret = llvm::ConstantInt::get(the_context, llvm::APInt(_cpl_int_width, _cpl_success));
}
void Dispatcher_llvm_gen::Dispatch(Return_statement& z) {
    if(!z.expr) {
        ret = builder->CreateRetVoid();
    }
    else {
        z.expr->Accept(*this);
        llvm::Value* val = ret;
        ret = builder->CreateRet(val);
    }
    hasReturn = true;
}
void Dispatcher_llvm_gen::Dispatch(Statement_list& z) {
    for(auto&y: z.statements) {
        y->Accept(*this);
        if(hasReturn) break;
        if(!ret) return;
    }
}
void Dispatcher_llvm_gen::Dispatch(StringLiteral& z) {
    curType = 4;
    ret = builder->CreateGlobalStringPtr(z.val.substr(1, z.val.length()-2));
}
void Dispatcher_llvm_gen::Dispatch(Ternary_op& z) {
    z.cond->Accept(*this);
    llvm::Value *CondV = ret;
    if (!CondV) assert(0);

    llvm::Function *TheFunction = builder->GetInsertBlock()->getParent();

    llvm::BasicBlock *ThenBB = llvm::BasicBlock::Create(the_context, "then", TheFunction);
    llvm::BasicBlock *ElseBB = llvm::BasicBlock::Create(the_context, "else");
    llvm::BasicBlock *MergeBB = llvm::BasicBlock::Create(the_context, "ifcont");

    builder->CreateCondBr(CondV, ThenBB, ElseBB);

    builder->SetInsertPoint(ThenBB);

    z.exp1->Accept(*this);
    llvm::Value *ThenV = ret;
    if (!ThenV) assert(0);

    builder->CreateBr(MergeBB);
    ThenBB = builder->GetInsertBlock();

    TheFunction->getBasicBlockList().push_back(ElseBB);
    builder->SetInsertPoint(ElseBB);

    z.exp2->Accept(*this);
    llvm::Value *ElseV = ret;
    if (!ElseV) assert(0);

    builder->CreateBr(MergeBB);
    ElseBB = builder->GetInsertBlock();

    TheFunction->getBasicBlockList().push_back(MergeBB);
    builder->SetInsertPoint(MergeBB);
    llvm::PHINode *PN = nullptr;

    if (curType == 0 || curType == 2) {
        PN = builder->CreatePHI(llvm::Type::getInt32Ty(the_context), 2, "iftmp");
    } else if (curType == 3) {
        PN = builder->CreatePHI(llvm::Type::getInt1Ty(the_context), 2, "iftmp");
    } else if (curType == 1) {
        PN = builder->CreatePHI(llvm::Type::getInt8Ty(the_context), 2, "iftmp");
    } else if (curType == 4) {
        PN = builder->CreatePHI(llvm::Type::getInt8PtrTy(the_context), 2, "iftmp");
    } else {
        assert(0);
    }

    PN->addIncoming(ThenV, ThenBB);
    PN->addIncoming(ElseV, ElseBB);
    ret = PN;
}
void Dispatcher_llvm_gen::Dispatch(Unary_op& z) {
    z.expr->Accept(*this);
    if(z.op == "not") {
        ret = builder->CreateNot(ret, "not_tmp");
    }
    if(z.op == "+") {
        ret = ret;
    }
    if(z.op == "-") {
        ret = builder->CreateNeg(ret, "neg_tmp");
    }
}
void Dispatcher_llvm_gen::Dispatch(UnsignedLiteral& z) {
    curType = 2;
    ret = llvm::ConstantInt::get(the_context, llvm::APInt(_cpl_int_width, z.val));
}
void Dispatcher_llvm_gen::Dispatch(Var_decl& z) {
    var_type.add_context(make_pair(z.id, typeMap.at(z.type)));
    if(isGlobal) {
        llvm::Type* typ = nullptr;

        if(typeMap.at(z.type) == -1) {assert(0);}
        else if(typeMap.at(z.type) == 0) {typ = llvm::Type::getInt32Ty(the_context);}
        else if(typeMap.at(z.type) == 1) {typ = llvm::Type::getInt8Ty(the_context);}
        else if(typeMap.at(z.type) == 2) {typ = llvm::Type::getInt32Ty(the_context);}
        else if(typeMap.at(z.type) == 3) {typ = llvm::Type::getInt1Ty(the_context);}
        else if(typeMap.at(z.type) == 4) {assert(0);}

        if(!typ) assert(0);

        int cnt = 0;
        if(z.shapex) ++cnt;
        if(z.shapey) ++cnt;

        if (cnt == 2) {
            llvm::ArrayType *arr_type = llvm::ArrayType::get(typ, ((*z.shapex)*(*z.shapey)));
            llvm::GlobalVariable *gv = new llvm::GlobalVariable(*the_module, arr_type, false,
                                                    llvm::GlobalValue::ExternalLinkage, nullptr,
                                                    z.id);
            gv->setInitializer(llvm::Constant::getNullValue(arr_type));
            arr_sz.add_context(make_pair(z.id, *z.shapey));
        }
        else if (cnt == 1) {
            llvm::ArrayType *arr_type = llvm::ArrayType::get(typ, (*z.shapex));
            llvm::GlobalVariable *gv = new llvm::GlobalVariable(*the_module, arr_type, false,
                                                    llvm::GlobalValue::ExternalLinkage, nullptr,
                                                    z.id);
            gv->setInitializer(llvm::Constant::getNullValue(arr_type));
        }
        else if(cnt == 0) {
            llvm::GlobalVariable *gv = new llvm::GlobalVariable(*the_module, typ, false,
                                                    llvm::GlobalValue::ExternalLinkage, nullptr,
                                                    z.id);
            gv->setInitializer(llvm::Constant::getNullValue(typ));
        }
        ret = llvm::ConstantInt::get(the_context, llvm::APInt(_cpl_int_width, _cpl_success));
    }
    else {
        assert(!z.shapex and !z.shapey);
        llvm::Function* the_func = builder->GetInsertBlock()->getParent();
        llvm::Value* init = nullptr;
        llvm::AllocaInst *alloc = nullptr;
        if(typeMap.at(z.type) == -1) {assert(0);}
        else if(typeMap.at(z.type) == 0) {
            init = llvm::ConstantInt::get(the_context, llvm::APInt(_cpl_int_width, _cpl_success, true));
            alloc = create_entry_alloc(the_func, z.id, 0);
        }
        else if(typeMap.at(z.type) == 1) {
            init = llvm::ConstantInt::get(the_context, llvm::APInt(_cpl_char_width, _cpl_success));
            alloc = create_entry_alloc(the_func, z.id, 1);
        }
        else if(typeMap.at(z.type) == 2) {
            init = llvm::ConstantInt::get(the_context, llvm::APInt(_cpl_int_width, _cpl_success, true));
            alloc = create_entry_alloc(the_func, z.id, 2);
        }
        else if(typeMap.at(z.type) == 3) {
            init = llvm::ConstantInt::get(the_context, llvm::APInt(_cpl_bool_width, _cpl_success));
            alloc = create_entry_alloc(the_func, z.id, 3);
        }
        else if(typeMap.at(z.type) == 4) {assert(0);}

        builder->CreateStore(init, alloc);

        named_values.add_context(make_pair(z.id, alloc));

        if(z.initial_value) {
            z.initial_value->Accept(*this);
            ret = builder->CreateStore(ret, alloc);
        }

        ret = llvm::ConstantInt::get(the_context, llvm::APInt(_cpl_int_width, _cpl_success));
    }
}
void Dispatcher_llvm_gen::Dispatch(Variable_list& z) {
    for(auto& y: z.decls) {
        y->Accept(*this);
        if(!ret) return;
    }
    ret = llvm::ConstantInt::get(the_context, llvm::APInt(_cpl_int_width, _cpl_success));
}
void Dispatcher_llvm_gen::Dispatch(While_statement& z) {
    llvm::Function *TheFunction = builder->GetInsertBlock()->getParent();

    int oldsz = named_values.get_context_size();
    int oldsz2 = var_type.get_context_size();

    llvm::BasicBlock *LoopBB = llvm::BasicBlock::Create(the_context, "loop", TheFunction);

    llvm::BasicBlock *AfterBB =
        llvm::BasicBlock::Create(the_context, "afterloop", TheFunction);

    z.cond->Accept(*this);
    llvm::Value *StartCond = ret;
    if (!StartCond) assert(0);
    builder->CreateCondBr(StartCond, LoopBB, AfterBB);

    builder->SetInsertPoint(LoopBB);

    z.block->Accept(*this);
    assert(ret);

    z.cond->Accept(*this);
    llvm::Value *EndCond = ret;
    if (!EndCond) assert(0);

    builder->CreateCondBr(EndCond, LoopBB, AfterBB);

    builder->SetInsertPoint(AfterBB);

    named_values.resize_context(oldsz);
    var_type.resize_context(oldsz2);

    ret = llvm::ConstantInt::get(the_context, llvm::APInt(_cpl_int_width, _cpl_success));
    hasReturn = false;
}
