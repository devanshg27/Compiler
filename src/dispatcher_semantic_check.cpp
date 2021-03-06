#include <bits/stdc++.h>
#include "dispatcher_semantic_check.h"

using namespace std;

ostream& operator<<(ostream& s, const pair<string,vector<Type>>& p) {
    return s << p.first;
}

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
        cerr << "Wrong number of dimensions for array " << z.id << endl;
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
void Dispatcher_semantic_check::Dispatch(BooleanLiteral&) {
    retval = Type::BOOL;
}
void Dispatcher_semantic_check::Dispatch(CharacterLiteral&) {
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
        cerr << "Wrong number of dimensions for array " << z.id << endl;
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
    hasReturn = false;
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
                if(retval != Type::INT) {
                    cerr << "Array index must be an integer";
                    exit(0);
                }
                ++cnt;
            }
            if(y->second.second) {
                y->second.second->Accept(*this);
                if(retval != Type::INT) {
                    cerr << "Array index must be an integer";
                    exit(0);
                }
                ++cnt;
            }
            if(cnt != var_context.get_value(y->first).second) {
                cerr << "Wrong number of dimensions for array " << y->first << endl;
                exit(0);
            }
            if(var_context.get_value(y->first).first == Type::BOOL) {
                cerr << "Can't read boolean values.";
                exit(0);
            }
            delete y;
        }
        retval = Type::VOID;
        return;
    }
    vector<Type> temp;
    for(auto&p: z.p_list->parameters) {
        p->Accept(*this);
        temp.push_back(retval);
    }
    if(z.id == "int") {
        if(temp.size() != 1 or temp[0] == Type::VOID or temp[0] == Type::STRING) {
            cout << "can't convert parameter to int.";
        }
        retval = Type::INT;
        return;
    }
    if(z.id == "char") {
        if(temp.size() != 1 or temp[0] != Type::INT) {
            cout << "can't convert parameter to char.";
        }
        retval = Type::CHAR;
        return;
    }
    if(z.id == "unsigned") {
        if(temp.size() != 1 or temp[0] != Type::INT) {
            cout << "can't convert parameter to unsigned.";
        }
        retval = Type::UNSIGNED;
        return;
    }
    if(z.id == "bool") {
        if(temp.size() != 1 or temp[0] != Type::INT) {
            cout << "can't convert parameter to bool.";
        }
        retval = Type::BOOL;
        return;
    }
    if(z.id == "print") {
        retval = Type::VOID;
        if(std::find(temp.begin(), temp.end(), Type::VOID) != temp.end()) {
            cerr << "Can't print void value.";
            exit(0);
        }
        if(std::find(temp.begin(), temp.end(), Type::BOOL) != temp.end()) {
            cerr << "Can't print boolean value.";
            exit(0);
        }
        return;
    }
    else {
        auto func_description = func_context.get_value(make_pair(z.id, temp));
        retval = func_description;
    }
}
void Dispatcher_semantic_check::Dispatch(Function_call_statement& z) {
    z.fcall->Accept(*this);
}
void Dispatcher_semantic_check::Dispatch(Function_decl& z) {
    cur_func_return_type = typeMap.at(z.type);

    pair<pair<string,vector<Type>>, Type> temp;
    temp.first.first = z.id;
    if(z.id == "print") {
        cerr << "Can not have function with name print.";
        exit(0);
    }
    else if(z.id == "read") {
        cerr << "Can not have function with name read.";
        exit(0);
    }
    else if(z.id == "int") {
        cerr << "Can not have function with name int.";
        exit(0);
    }
    else if(z.id == "char") {
        cerr << "Can not have function with name char.";
        exit(0);
    }
    else if(z.id == "unsigned") {
        cerr << "Can not have function with name unsigned.";
        exit(0);
    }
    else if(z.id == "bool") {
        cerr << "Can not have function with name bool.";
        exit(0);
    }
    temp.second = typeMap.at(z.type);
    for(auto&y: z.a_list->arguments) {
        temp.first.second.push_back(typeMap.at(y->type));
    }
    func_context.add_context(temp);

    int oldsz = var_context.get_context_size();
    z.a_list->Accept(*this);
    z.blk->Accept(*this);
    if(cur_func_return_type != Type::VOID and !hasReturn) {
        cerr << "Non-void function " << z.id << " doesn't return a value.\n";
        exit(0);
    }
    hasReturn = false;
    var_context.resize_context(oldsz);
}
void Dispatcher_semantic_check::Dispatch(Function_list& z) {
    set<string> fids;
    for(auto& y: z.decls) {
        if(fids.find(y->id) != fids.end()) {
            cerr << "Function name collision." << endl;
            exit(0);
        }
        fids.insert(y->id);
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
        bool if_return = hasReturn;
        hasReturn = false;
        if(z.else_statement) {
            z.else_statement->Accept(*this);
            hasReturn = (hasReturn and if_return);
        }
    }
    else {
        z.block->Accept(*this);
    }
}
void Dispatcher_semantic_check::Dispatch(IntegerLiteral&) {
    retval = Type::INT;
}
void Dispatcher_semantic_check::Dispatch(Multivar_decl& z) {
    for(auto&y: z.decls) {
        y->Accept(*this);
    }
}
void Dispatcher_semantic_check::Dispatch(Parameter_list&) {
    assert(0);
}
void Dispatcher_semantic_check::Dispatch(Program& z) {
    isGlobal = true;
    z.v_list->Accept(*this);
    isGlobal = false;
    z.f_list->Accept(*this);
    auto func_description = func_context.get_value(make_pair("main", vector<Type>()));
    if(func_description != Type::INT) {
        cerr << "main should be declared as int main().";
        exit(0);
    }
    retval = func_description;
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
    hasReturn = true;
}
void Dispatcher_semantic_check::Dispatch(Statement_list& z) {
    for(auto&y: z.statements) {
        y->Accept(*this);
    }
}
void Dispatcher_semantic_check::Dispatch(StringLiteral&) {
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
void Dispatcher_semantic_check::Dispatch(UnsignedLiteral&) {
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
    if(cnt and !isGlobal) {
        cerr << "Arrays only allowed as global variable.";
        exit(0);
    }
    if(isGlobal and z.initial_value) {
        cerr << "Global variables can't be initialized, they are zero initialized by default.";
        exit(0);
    }
    temp.second = {typeMap.at(z.type), cnt};
    if(z.initial_value) {
        z.initial_value->Accept(*this);
        if(retval != typeMap.at(z.type)) {
            cerr << "RHS during Assignment must be of same type as variable";
            exit(0);
        }
    }
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
    hasReturn = false;
}