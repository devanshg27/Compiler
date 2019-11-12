#include <bits/stdc++.h>
#include "dispatcher_semantic_check.h"

using namespace std;

const map<string,Type> typeMap = {
    {"int", Type::INT},
    {"char", Type::CHAR},
    {"void", Type::VOID},
    {"unsigned", Type::UNSIGNED},
    {"bool", Type::BOOL}
};

void Dispatcher_semantic_check::Dispatch(Argument_list& z) {
    for(auto&y: z.arguments) {
        if(y->shapex || y->shapey) {
            cerr << "Arrays can't be used as arguments.";
            exit(0);
        }
        if(y->initial_value) {
            cerr << "Default arguments are not supported yet.";
            exit(0);
        }
        y->Accept(*this);
    }
}
void Dispatcher_semantic_check::Dispatch(Assignment_statement& z) {
    int cnt = 0;
    if(z.posx) {
        z.posx->Accept(*this);
        if(retval != Type::INT) {
            cerr << "Array index must be an integer";
            exit(0);
        }
        ++cnt;
    }
    if(z.posy) {
        z.posy->Accept(*this);
        if(retval != Type::INT) {
            cerr << "Array index must be an integer";
            exit(0);
        }
        ++cnt;
    }
    if(cnt != var_context.get_value(z.id).second) {
        cerr << "Wrong number of dimensions for array";
        exit(0);
    }
    z.expr->Accept(*this);
    if(retval != var_context.get_value(z.id).first) {
        cerr << "RHS during Assignment must be of same type as variable";
        exit(0);
    }
}
void Dispatcher_semantic_check::Dispatch(Binary_op& z) {
    z.exp1->Accept(*this);
    Type ret1 = retval;
    z.exp2->Accept(*this);
    Type ret2 = retval;
    if(ret1 != ret2) {
        cerr << "Type mismatch";
        exit(0);
    }
    if(z.op == "+" or z.op == "-" or z.op == "*" or z.op == "/" or z.op == "%") {
        retval = ret1;
        if(retval != Type::INT and retval != Type::UNSIGNED) {
            cerr << "Type mismatch";
            exit(0);
        }
    }
    if(z.op == "or" or z.op == "and" or z.op == "xor") {
        retval = ret1;
        if(retval != Type::BOOL) {
            cerr << "Type mismatch";
            exit(0);
        }
    }
    if(z.op == "<" or z.op == ">" or z.op == "<=" or z.op == ">=" or z.op == "==" or z.op == "!=") {
        retval = Type::BOOL;
        if(ret1 != Type::INT and ret1 != Type::UNSIGNED) {
            cerr << "Type mismatch";
            exit(0);
        }
    }
}
void Dispatcher_semantic_check::Dispatch(Block& z) {
    int oldsz = var_context.get_context_size();
    z.v_list->Accept(*this);
    z.s_list->Accept(*this);
    var_context.resize_context(oldsz);
}
void Dispatcher_semantic_check::Dispatch(BlockStatement& z) {
    z.block->Accept(*this);
}
void Dispatcher_semantic_check::Dispatch(BooleanLiteral& z) {
    retval = Type::BOOL;
}
void Dispatcher_semantic_check::Dispatch(CharacterLiteral& z) {
    retval = Type::CHAR;
}
void Dispatcher_semantic_check::Dispatch(ExpressionBracketed& z) {
    z.expr->Accept(*this);
}
void Dispatcher_semantic_check::Dispatch(ExpressionFunctionCall& z) {
    z.fcall->Accept(*this);
}
void Dispatcher_semantic_check::Dispatch(ExpressionIdentifier& z) {
    int cnt = 0;
    if(z.posx) {
        z.posx->Accept(*this);
        if(retval != Type::INT) {
            cerr << "Array index must be an integer";
            exit(0);
        }
        ++cnt;
    }
    if(z.posy) {
        z.posy->Accept(*this);
        if(retval != Type::INT) {
            cerr << "Array index must be an integer";
            exit(0);
        }
        ++cnt;
    }
    if(cnt != var_context.get_value(z.id).second) {
        cerr << "Wrong number of dimensions for array";
        exit(0);
    }
    retval = var_context.get_value(z.id).first;
}
void Dispatcher_semantic_check::Dispatch(ExpressionLiteral& z) {
    z.expr->Accept(*this);
}
void Dispatcher_semantic_check::Dispatch(For_statement& z) {
    int oldsz = var_context.get_context_size();
    if(z.decls) z.decls->Accept(*this);
    z.cond->Accept(*this);
    if(retval != Type::BOOL) {
        cerr << "Condition in for must be boolean";
        exit(0);
    }
    if(z.upd) z.upd->Accept(*this);
    z.block->Accept(*this);
    var_context.resize_context(oldsz);
}
void Dispatcher_semantic_check::Dispatch(Function_call& z) {
    if(z.id == "read") {
        for(auto&p: z.p_list->parameters) {
            auto y = p->getIdentifier();
            if(y == NULL) {
                cerr << "read must be given an identifier as parameter.";
                exit(0);
            }
            int cnt = 0;
            if(y->second.first) {
                y->second.first->Accept(*this);
                ++cnt;
            }
            if(y->second.second) {
                y->second.second->Accept(*this);
                ++cnt;
            }
            if(cnt != var_context.get_value(y->first).second) {
                cerr << "Wrong number of dimensions for array";
                exit(0);
            }
            delete y;
        }
        return;
    }
    vector<Type> temp;
    for(auto&p: z.p_list->parameters) {
        p->Accept(*this);
        temp.push_back(retval);
    }
    if(z.id == "print") {
        return;
    }
    else {
        auto func_description = func_context.get_value(z.id);
        if(temp != func_description.second) {
            cerr << "Parameter and arguments don\'t match for "<< z.id <<" .";
            exit(0);
        }
        retval = func_description.first;
    }
}
void Dispatcher_semantic_check::Dispatch(Function_call_statement& z) {
    z.fcall->Accept(*this);
}
void Dispatcher_semantic_check::Dispatch(Function_decl& z) {
    cur_func_return_type = typeMap.at(z.type);
    
    pair<string, pair<Type, vector<Type>>> temp;
    temp.first = z.id;
    if(z.id == "print") {
        cerr << "Can not have function with name print.";
        exit(0);
    }
    else if(z.id == "read") {
        cerr << "Can not have function with name read.";
        exit(0);
    }
    temp.second.first = typeMap.at(z.type);
    for(auto&y: z.a_list->arguments) {
        temp.second.second.push_back(typeMap.at(y->type));
    }
    func_context.add_context(temp);

    int oldsz = var_context.get_context_size();
    z.a_list->Accept(*this);
    z.blk->Accept(*this);
    var_context.resize_context(oldsz);
}
void Dispatcher_semantic_check::Dispatch(Function_list& z) {
    for(auto& y: z.decls) {
        y->Accept(*this);
    }
}
void Dispatcher_semantic_check::Dispatch(If_statement& z) {
    if(z.cond) {
        z.cond->Accept(*this);
        if(retval != Type::BOOL) {
            cerr << "Condition in if must be boolean";
            exit(0);
        }
        z.block->Accept(*this);
        if(z.else_statement) {
            z.else_statement->Accept(*this);
        }
    }
    else {
        z.block->Accept(*this);
    }
}
void Dispatcher_semantic_check::Dispatch(IntegerLiteral& z) {
    retval = Type::INT;
}
void Dispatcher_semantic_check::Dispatch(Multivar_decl& z) {
    for(auto&y: z.decls) {
        y->Accept(*this);
    }
}
void Dispatcher_semantic_check::Dispatch(Parameter_list& z) {
    assert(0);
}
void Dispatcher_semantic_check::Dispatch(Program& z) {
    z.v_list->Accept(*this);
    z.f_list->Accept(*this);
}
void Dispatcher_semantic_check::Dispatch(Return_statement& z) {
    if(z.expr) {
        z.expr->Accept(*this);
        if(retval != cur_func_return_type) {
            cerr << "Returned value type does not match function's return type.";
            exit(0);
        }
    }
    else {
        if(cur_func_return_type != Type::VOID) {
            cerr << "Non-void function must return a value.";
            exit(0);
        }
    }
}
void Dispatcher_semantic_check::Dispatch(Statement_list& z) {
    for(auto&y: z.statements) {
        y->Accept(*this);
    }
}
void Dispatcher_semantic_check::Dispatch(StringLiteral& z) {
    retval = Type::STRING;
}
void Dispatcher_semantic_check::Dispatch(Ternary_op& z) {
    z.cond->Accept(*this);
    if(retval != Type::BOOL) {
        cerr << "Type mismatch";
        exit(0);
    }
    z.exp1->Accept(*this);
    Type ret1 = retval;
    z.exp2->Accept(*this);
    Type ret2 = retval;
    if(ret1 != ret2) {
        cerr << "Type mismatch";
        exit(0);
    }
    retval = ret1;
}
void Dispatcher_semantic_check::Dispatch(Unary_op& z) {
    z.expr->Accept(*this);
    if(z.op == "not") {
        if(retval != Type::BOOL) {
            cerr << "Type mismatch";
            exit(0);
        }
    }
    if(z.op == "+" or z.op == "-") {
        if(retval != Type::INT and retval != Type::UNSIGNED) {
            cerr << "Type mismatch";
            exit(0);
        }
    }
}
void Dispatcher_semantic_check::Dispatch(UnsignedLiteral& z) {
    retval = Type::UNSIGNED;
}
void Dispatcher_semantic_check::Dispatch(Var_decl& z) {
    pair<string, pair<Type, int>> temp;
    int cnt = 0;
    if(z.shapex) ++cnt;
    if(z.shapey) ++cnt;
    temp.first = z.id;
    if(z.type == "void") {
        cerr << "Variables can't be of type void.";
        exit(0);
    }
    temp.second = {typeMap.at(z.type), cnt};
    var_context.add_context(temp);
}
void Dispatcher_semantic_check::Dispatch(Variable_list& z) {
    for(auto& y: z.decls) {
        y->Accept(*this);
    }
}
void Dispatcher_semantic_check::Dispatch(While_statement& z) {
    z.cond->Accept(*this);
    if(retval != Type::BOOL) {
        cerr << "Condition in while must be boolean";
        exit(0);
    }
    z.block->Accept(*this);
}