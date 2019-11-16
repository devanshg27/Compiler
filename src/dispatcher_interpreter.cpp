#include <bits/stdc++.h>
#include "dispatcher_interpreter.h"

using namespace std;

const map<string,int> typeMap = {
    {"void", -1},
    {"int", 0},
    {"char", 1},
    {"unsigned", 2},
    {"bool", 3},
    {"string", 4}
};

void Dispatcher_interpreter::Dispatch(Argument_list& z) {
    for(auto&y: z.arguments) {
        y->Accept(*this);
    }
}
void Dispatcher_interpreter::Dispatch(Assignment_statement& z) {
    int cnt = 0, pos_x, pos_y;
    if(z.posx) {
        z.posx->Accept(*this);
        pos_x = std::get<Container<int>>(retval).get_reference();
        ++cnt;
    }
    if(z.posy) {
        z.posy->Accept(*this);
        pos_y = std::get<Container<int>>(retval).get_reference();
        ++cnt;
    }
    z.expr->Accept(*this);
    if(retval.index() == 0) {
        if(cnt==0) std::get<0>(var_context.get_value(z.id)).get_reference() = std::get<0>(retval).get_reference();
        if(cnt==1) std::get<0>(var_context.get_value(z.id)).get_reference(pos_x) = std::get<0>(retval).get_reference();
        if(cnt==2) std::get<0>(var_context.get_value(z.id)).get_reference(pos_x, pos_y) = std::get<0>(retval).get_reference();
    }
    if(retval.index() == 1) {
        if(cnt==0) std::get<1>(var_context.get_value(z.id)).get_reference() = std::get<1>(retval).get_reference();
        if(cnt==1) std::get<1>(var_context.get_value(z.id)).get_reference(pos_x) = std::get<1>(retval).get_reference();
        if(cnt==2) std::get<1>(var_context.get_value(z.id)).get_reference(pos_x, pos_y) = std::get<1>(retval).get_reference();
    }
    if(retval.index() == 2) {
        if(cnt==0) std::get<2>(var_context.get_value(z.id)).get_reference() = std::get<2>(retval).get_reference();
        if(cnt==1) std::get<2>(var_context.get_value(z.id)).get_reference(pos_x) = std::get<2>(retval).get_reference();
        if(cnt==2) std::get<2>(var_context.get_value(z.id)).get_reference(pos_x, pos_y) = std::get<2>(retval).get_reference();
    }
    if(retval.index() == 3) {
        if(cnt==0) std::get<3>(var_context.get_value(z.id)).get_reference() = std::get<3>(retval).get_reference();
        if(cnt==1) std::get<3>(var_context.get_value(z.id)).get_reference(pos_x) = std::get<3>(retval).get_reference();
        if(cnt==2) std::get<3>(var_context.get_value(z.id)).get_reference(pos_x, pos_y) = std::get<3>(retval).get_reference();
    }
    if(retval.index() == 4) {
        assert(0);
    }
}
void Dispatcher_interpreter::Dispatch(Binary_op& z) {
    z.exp1->Accept(*this);
    ValueContainer ret1 = std::move(retval);
    z.exp2->Accept(*this);
    ValueContainer ret2 = std::move(retval);
    if(z.op == "+" or z.op == "-" or z.op == "*" or z.op == "/" or z.op == "%") {
        if(ret1.index() == 0) {
            retval = Container<int>();
            int val1 = std::get<0>(ret1).get_reference();
            int val2 = std::get<0>(ret2).get_reference();
            if(z.op == "+") std::get<0>(retval).get_reference() = val1 + val2;
            if(z.op == "-") std::get<0>(retval).get_reference() = val1 - val2;
            if(z.op == "*") std::get<0>(retval).get_reference() = val1 * val2;
            if(z.op == "/") std::get<0>(retval).get_reference() = val1 / val2;
            if(z.op == "%") std::get<0>(retval).get_reference() = val1 % val2;
        }
        if(ret1.index() == 2) {
            retval = Container<unsigned>();
            unsigned val1 = std::get<2>(ret1).get_reference();
            unsigned val2 = std::get<2>(ret2).get_reference();
            if(z.op == "+") std::get<2>(retval).get_reference() = val1 + val2;
            if(z.op == "-") std::get<2>(retval).get_reference() = val1 - val2;
            if(z.op == "*") std::get<2>(retval).get_reference() = val1 * val2;
            if(z.op == "/") std::get<2>(retval).get_reference() = val1 / val2;
            if(z.op == "%") std::get<2>(retval).get_reference() = val1 % val2;
        }
    }
    if(z.op == "or" or z.op == "and" or z.op == "xor") {
        bool val1 = std::get<3>(ret1).get_reference();
        bool val2 = std::get<3>(ret2).get_reference();
        retval = Container<bool>();
        if(z.op == "or") std::get<3>(retval).get_reference() = (val1 || val2);
        if(z.op == "and") std::get<3>(retval).get_reference() = (val1 && val2);
        if(z.op == "xor") std::get<3>(retval).get_reference() = (val1 != val2);
    }
    if(z.op == "<" or z.op == ">" or z.op == "<=" or z.op == ">=" or z.op == "==" or z.op == "!=") {
        retval = Container<bool>();
        if(ret1.index() == 0) {
            int val1 = std::get<0>(ret1).get_reference();
            int val2 = std::get<0>(ret2).get_reference();
            if(z.op == "<") std::get<3>(retval).get_reference() = val1 < val2;
            if(z.op == "<=") std::get<3>(retval).get_reference() = val1 <= val2;
            if(z.op == ">") std::get<3>(retval).get_reference() = val1 > val2;
            if(z.op == ">=") std::get<3>(retval).get_reference() = val1 >= val2;
            if(z.op == "==") std::get<3>(retval).get_reference() = val1 == val2;
            if(z.op == "!=") std::get<3>(retval).get_reference() = val1 != val2;
        }
        if(ret1.index() == 2) {
            unsigned val1 = std::get<2>(ret1).get_reference();
            unsigned val2 = std::get<2>(ret2).get_reference();
            if(z.op == "<") std::get<3>(retval).get_reference() = val1 < val2;
            if(z.op == "<=") std::get<3>(retval).get_reference() = val1 <= val2;
            if(z.op == ">") std::get<3>(retval).get_reference() = val1 > val2;
            if(z.op == ">=") std::get<3>(retval).get_reference() = val1 >= val2;
            if(z.op == "==") std::get<3>(retval).get_reference() = val1 == val2;
            if(z.op == "!=") std::get<3>(retval).get_reference() = val1 != val2;
        }
    }
}
void Dispatcher_interpreter::Dispatch(Block& z) {
    int oldsz = var_context.get_context_size();
    z.v_list->Accept(*this);
    z.s_list->Accept(*this);
    var_context.resize_context(oldsz);
}
void Dispatcher_interpreter::Dispatch(BlockStatement& z) {
    z.block->Accept(*this);
}
void Dispatcher_interpreter::Dispatch(BooleanLiteral& z) {
    retval = Container<bool>();
    std::get<Container<bool>>(retval).get_reference() = z.val;
}
void Dispatcher_interpreter::Dispatch(CharacterLiteral& z) {
    retval = Container<char>();
    std::get<Container<char>>(retval).get_reference() = z.val;
}
void Dispatcher_interpreter::Dispatch(ExpressionBracketed& z) {
    z.expr->Accept(*this);
}
void Dispatcher_interpreter::Dispatch(ExpressionFunctionCall& z) {
    z.fcall->Accept(*this);
}
void Dispatcher_interpreter::Dispatch(ExpressionIdentifier& z) {
    int cnt = 0, pos_x, pos_y;
    if(z.posx) {
        z.posx->Accept(*this);
        pos_x = std::get<Container<int>>(retval).get_reference();
        ++cnt;
    }
    if(z.posy) {
        z.posy->Accept(*this);
        pos_y = std::get<Container<int>>(retval).get_reference();
        ++cnt;
    }
    int curidx = var_context.get_value(z.id).index();
    if(curidx == 0) {
        retval = Container<int>();
        if(cnt==0) std::get<0>(retval).get_reference() = std::get<0>(var_context.get_value(z.id)).get_reference();
        if(cnt==1) std::get<0>(retval).get_reference() = std::get<0>(var_context.get_value(z.id)).get_reference(pos_x);
        if(cnt==2) std::get<0>(retval).get_reference() = std::get<0>(var_context.get_value(z.id)).get_reference(pos_x, pos_y);
    }
    if(curidx == 1) {
        retval = Container<char>();
        if(cnt==0) std::get<1>(retval).get_reference() = std::get<1>(var_context.get_value(z.id)).get_reference();
        if(cnt==1) std::get<1>(retval).get_reference() = std::get<1>(var_context.get_value(z.id)).get_reference(pos_x);
        if(cnt==2) std::get<1>(retval).get_reference() = std::get<1>(var_context.get_value(z.id)).get_reference(pos_x, pos_y);
    }
    if(curidx == 2) {
        retval = Container<unsigned>();
        if(cnt==0) std::get<2>(retval).get_reference() = std::get<2>(var_context.get_value(z.id)).get_reference();
        if(cnt==1) std::get<2>(retval).get_reference() = std::get<2>(var_context.get_value(z.id)).get_reference(pos_x);
        if(cnt==2) std::get<2>(retval).get_reference() = std::get<2>(var_context.get_value(z.id)).get_reference(pos_x, pos_y);
    }
    if(curidx == 3) {
        retval = Container<bool>();
        if(cnt==0) std::get<3>(retval).get_reference() = std::get<3>(var_context.get_value(z.id)).get_reference();
        if(cnt==1) std::get<3>(retval).get_reference() = std::get<3>(var_context.get_value(z.id)).get_reference(pos_x);
        if(cnt==2) std::get<3>(retval).get_reference() = std::get<3>(var_context.get_value(z.id)).get_reference(pos_x, pos_y);
    }
    if(curidx == 4) {
        assert(0);
    }
}
void Dispatcher_interpreter::Dispatch(ExpressionLiteral& z) {
    z.expr->Accept(*this);
}
void Dispatcher_interpreter::Dispatch(For_statement& z) {
    if(hasReturned) return;
    int oldsz = var_context.get_context_size();
    if(z.decls) z.decls->Accept(*this);
    while(!hasReturned) {
        z.cond->Accept(*this);
        if(std::get<3>(retval).get_reference() == false) break;
        z.block->Accept(*this);
        if(hasReturned) break;
        if(z.upd) z.upd->Accept(*this);
    }
    var_context.resize_context(oldsz);
}
void Dispatcher_interpreter::Dispatch(Function_call& z) {
    if(z.id == "print") {
        for(auto&p: z.p_list->parameters) {
            p->Accept(*this);
            if(retval.index() == 0) cout << std::get<0>(retval).get_reference();
            if(retval.index() == 1) cout << std::get<1>(retval).get_reference();
            if(retval.index() == 2) cout << std::get<2>(retval).get_reference();
            if(retval.index() == 3) cout << std::get<3>(retval).get_reference();
            if(retval.index() == 4) cout << std::get<4>(retval);
        }
        return;
    }
    if(z.id == "read") {
        for(auto&p: z.p_list->parameters) {
            auto y = p->getIdentifier();
            int cnt = 0, pos_x, pos_y;
            if(y->second.first) {
                y->second.first->Accept(*this);
                pos_x = std::get<Container<int>>(retval).get_reference();
                ++cnt;
            }
            if(y->second.second) {
                y->second.second->Accept(*this);
                pos_y = std::get<Container<int>>(retval).get_reference();
                ++cnt;
            }
            if(var_context.get_value(y->first).index() == 0) {
                if(cnt==0) cin >> std::get<0>(var_context.get_value(y->first)).get_reference();
                if(cnt==1) cin >> std::get<0>(var_context.get_value(y->first)).get_reference(pos_x);
                if(cnt==2) cin >> std::get<0>(var_context.get_value(y->first)).get_reference(pos_x, pos_y);
            }
            if(var_context.get_value(y->first).index() == 1) {
                if(cnt==0) cin >> std::get<1>(var_context.get_value(y->first)).get_reference();
                if(cnt==1) cin >> std::get<1>(var_context.get_value(y->first)).get_reference(pos_x);
                if(cnt==2) cin >> std::get<1>(var_context.get_value(y->first)).get_reference(pos_x, pos_y);
            }
            if(var_context.get_value(y->first).index() == 2) {
                if(cnt==0) cin >> std::get<2>(var_context.get_value(y->first)).get_reference();
                if(cnt==1) cin >> std::get<2>(var_context.get_value(y->first)).get_reference(pos_x);
                if(cnt==2) cin >> std::get<2>(var_context.get_value(y->first)).get_reference(pos_x, pos_y);
            }
            if(var_context.get_value(y->first).index() == 3) {
                if(cnt==0) cin >> std::get<3>(var_context.get_value(y->first)).get_reference();
                if(cnt==1) cin >> std::get<3>(var_context.get_value(y->first)).get_reference(pos_x);
                if(cnt==2) cin >> std::get<3>(var_context.get_value(y->first)).get_reference(pos_x, pos_y);
            }
            if(var_context.get_value(y->first).index() == 4) {
                assert(0);
            }
            delete y;
        }
        return;
    }
    Function_decl* fd = func_context.get_value(z.id);
    int oldsz = var_context.get_context_size();
    for(int i=0; i<(int)fd->a_list->arguments.size(); ++i) {
        z.p_list->parameters[i]->Accept(*this);

        Var_decl* vd = fd->a_list->arguments[i];

        if(typeMap.at(vd->type) == -1) {assert(0);}
        if(typeMap.at(vd->type) == 0) {
            var_context.add_context(vd->id, std::move(Container<int>()));
            std::get<0>(var_context.get_value(vd->id)).get_reference() = std::get<0>(retval).get_reference();
        }
        if(typeMap.at(vd->type) == 1) {
            var_context.add_context(vd->id, std::move(Container<char>()));
            std::get<1>(var_context.get_value(vd->id)).get_reference() = std::get<1>(retval).get_reference();
        }
        if(typeMap.at(vd->type) == 2) {
            var_context.add_context(vd->id, std::move(Container<unsigned>()));
            std::get<2>(var_context.get_value(vd->id)).get_reference() = std::get<2>(retval).get_reference();
        }
        if(typeMap.at(vd->type) == 3) {
            var_context.add_context(vd->id, std::move(Container<bool>()));
            std::get<3>(var_context.get_value(vd->id)).get_reference() = std::get<3>(retval).get_reference();
        }
        if(typeMap.at(vd->type) == 4) {assert(0);}
    }
    fd->blk->Accept(*this);
    swap(func_retval, retval);
    if(!hasReturned and typeMap.at(fd->type) >= 0) {
        cerr << "Runtime error: No value returned from non-void function " << fd->id;
        exit(0);
    } 
    hasReturned = false;
    var_context.resize_context(oldsz);
}
void Dispatcher_interpreter::Dispatch(Function_call_statement& z) {
    z.fcall->Accept(*this);
}
void Dispatcher_interpreter::Dispatch(Function_decl& z) {
    func_context.add_context({z.id, &z});
}
void Dispatcher_interpreter::Dispatch(Function_list& z) {
    for(auto& y: z.decls) {
        y->Accept(*this);
    }
}
void Dispatcher_interpreter::Dispatch(If_statement& z) {
    if(z.cond) {
        z.cond->Accept(*this);
        if(std::get<3>(retval).get_reference()) {
            z.block->Accept(*this);
        }
        else if(z.else_statement) {
            z.else_statement->Accept(*this);
        }
    }
    else {
        z.block->Accept(*this);
    }
}
void Dispatcher_interpreter::Dispatch(IntegerLiteral& z) {
    retval = Container<int>();
    std::get<Container<int>>(retval).get_reference() = z.val;
}
void Dispatcher_interpreter::Dispatch(Multivar_decl& z) {
    for(auto&y: z.decls) {
        y->Accept(*this);
    }
}
void Dispatcher_interpreter::Dispatch(Parameter_list& z) {
    assert(0);
}
void Dispatcher_interpreter::Dispatch(Program& z) {
    z.v_list->Accept(*this);
    z.f_list->Accept(*this);
    Function_decl* fd = func_context.get_value("main");
    fd->blk->Accept(*this);
    if(!hasReturned and typeMap.at(fd->type) >= 0) {
        cerr << "Runtime error: Program ended without returning status code." << fd->id;
        exit(0);
    }
    else {
        cout << "Program ended with status code " << std::get<0>(func_retval).get_reference() << ".";
    }
    hasReturned = false;
}
void Dispatcher_interpreter::Dispatch(Return_statement& z) {
    hasReturned = true;
    if(z.expr) {
        z.expr->Accept(*this);
        swap(retval, func_retval);
    }
}
void Dispatcher_interpreter::Dispatch(Statement_list& z) {
    if(hasReturned) return;
    for(auto&y: z.statements) {
        y->Accept(*this);
        if(hasReturned) break;
    }
}
void Dispatcher_interpreter::Dispatch(StringLiteral& z) {
    assert((int)z.val.size() >= 2);
    retval = z.val.substr(1, z.val.length() - 2);
}
void Dispatcher_interpreter::Dispatch(Ternary_op& z) {
    z.cond->Accept(*this);
    if(std::get<3>(retval).get_reference()) {
        z.exp1->Accept(*this);
    }
    else {
        z.exp2->Accept(*this);
    }
}
void Dispatcher_interpreter::Dispatch(Unary_op& z) {
    z.expr->Accept(*this);
    if(z.op == "not") {
        std::get<3>(retval).get_reference() = ! std::get<3>(retval).get_reference();
    }
    if(z.op == "+" or z.op == "-") {
        if(retval.index() == 0) {
            if(z.op == "-") std::get<0>(retval).get_reference() = ! std::get<0>(retval).get_reference();
        }
        if(retval.index() == 2) {
            if(z.op == "-") std::get<2>(retval).get_reference() = ! std::get<2>(retval).get_reference();
        }
    }
}
void Dispatcher_interpreter::Dispatch(UnsignedLiteral& z) {
    retval = Container<unsigned>();
    std::get<Container<unsigned>>(retval).get_reference() = z.val;
}
void Dispatcher_interpreter::Dispatch(Var_decl& z) {
    int cnt = 0;
    if(z.shapex) ++cnt;
    if(z.shapey) ++cnt;

    if(typeMap.at(z.type) == -1) {assert(0);}
    if(typeMap.at(z.type) == 0) {
        if(cnt==0) var_context.add_context(z.id, std::move(Container<int>()));
        if(cnt==1) var_context.add_context(z.id, std::move(Container<int>(*z.shapex)));
        if(cnt==2) var_context.add_context(z.id, std::move(Container<int>(*z.shapex, *z.shapey)));
        if(z.initial_value) {
            z.initial_value->Accept(*this);
            if(cnt==0) std::get<0>(var_context.get_value(z.id)).get_reference() = std::get<0>(retval).get_reference();
        }
    }
    if(typeMap.at(z.type) == 1) {
        if(cnt==0) var_context.add_context(z.id, std::move(Container<char>()));
        if(cnt==1) var_context.add_context(z.id, std::move(Container<char>(*z.shapex)));
        if(cnt==2) var_context.add_context(z.id, std::move(Container<char>(*z.shapex, *z.shapey)));
        if(z.initial_value) {
            z.initial_value->Accept(*this);
            if(cnt==0) std::get<1>(var_context.get_value(z.id)).get_reference() = std::get<1>(retval).get_reference();
        }
    }
    if(typeMap.at(z.type) == 2) {
        if(cnt==0) var_context.add_context(z.id, std::move(Container<unsigned>()));
        if(cnt==1) var_context.add_context(z.id, std::move(Container<unsigned>(*z.shapex)));
        if(cnt==2) var_context.add_context(z.id, std::move(Container<unsigned>(*z.shapex, *z.shapey)));
        if(z.initial_value) {
            z.initial_value->Accept(*this);
            if(cnt==0) std::get<2>(var_context.get_value(z.id)).get_reference() = std::get<2>(retval).get_reference();
        }
    }
    if(typeMap.at(z.type) == 3) {
        if(cnt==0) var_context.add_context(z.id, std::move(Container<bool>()));
        if(cnt==1) var_context.add_context(z.id, std::move(Container<bool>(*z.shapex)));
        if(cnt==2) var_context.add_context(z.id, std::move(Container<bool>(*z.shapex, *z.shapey)));
        if(z.initial_value) {
            z.initial_value->Accept(*this);
            if(cnt==0) std::get<3>(var_context.get_value(z.id)).get_reference() = std::get<3>(retval).get_reference();
        }
    }
    if(typeMap.at(z.type) == 4) {assert(0);}
}
void Dispatcher_interpreter::Dispatch(Variable_list& z) {
    for(auto& y: z.decls) {
        y->Accept(*this);
    }
}
void Dispatcher_interpreter::Dispatch(While_statement& z) {
    if(hasReturned) return;
    while(!hasReturned) {
        z.cond->Accept(*this);
        if(std::get<3>(retval).get_reference() == false) break;
        z.block->Accept(*this);
    }
}