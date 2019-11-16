#include <bits/stdc++.h>
#include "dispatcher_pretty_print.h"

using namespace std;

void Dispatcher_pretty_print::Dispatch(Argument_list& z) {
    for ( int i = 0; i < (int)z.arguments.size(); ++i ) {
        cout <<z.arguments[i]->type << " " << z.arguments[i]->id;
        if(z.arguments[i]->shapex) {
            cout<<"["<<*(z.arguments[i]->shapex)<<"]";
        }
        if(z.arguments[i]->shapey) {
            cout<<"["<<*(z.arguments[i]->shapey)<<"]";
        }
        if(z.arguments[i]->initial_value) {
            cout<<" = ";
            z.arguments[i]->initial_value->Accept(*this);
        }
        if(i != (int)z.arguments.size() - 1) cout <<", ";
    }
}
void Dispatcher_pretty_print::Dispatch(Assignment_statement& z) {
    cout << z.id;
    if(z.posx) {
        cout<<"[ ";
        z.posx->Accept(*this);
        cout<<" ]";
    }
    if(z.posy) {
        cout<<"[ ";
        z.posy->Accept(*this);
        cout<<" ]";
    }
    cout << " = ";
    z.expr->Accept(*this);
    if(!isFor) cout<<";";
}
void Dispatcher_pretty_print::Dispatch(Binary_op& z) {
    z.exp1->Accept(*this);
    cout << " " << z.op << " ";
    z.exp2->Accept(*this);
}
void Dispatcher_pretty_print::Dispatch(Block& z) {
    cout << "{\n";
    ++tabs;
    z.v_list->Accept(*this);
    z.s_list->Accept(*this);
    --tabs;
    for (int i = 0; i < tabs; i++) {
        cout<<"    ";
    }
    cout << "} ";
}
void Dispatcher_pretty_print::Dispatch(BlockStatement& z) {
    z.block->Accept(*this);
}
void Dispatcher_pretty_print::Dispatch(BooleanLiteral& z) {
    if(z.val) {
        cout << "true";
    }
    else {
        cout << "false";
    }
}
void Dispatcher_pretty_print::Dispatch(CharacterLiteral& z) {
    cout<<'\'';
    if(z.val == '\n') {
        cout << "\\n";
    }
    else if(z.val == '\r') {
        cout << "\\r";
    }
    else if(z.val == '\t') {
        cout << "\\t";
    }
    else if(z.val == '\'') {
        cout << "\\\'";
    }
    else if(z.val == '\"') {
        cout << "\\\"";
    }
    else if(z.val == '\\') {
        cout << "\\\\";
    }
    else {
        cout << z.val;
    }
    cout<<'\'';
}
void Dispatcher_pretty_print::Dispatch(ExpressionBracketed& z) {
    cout << "( ";
    z.expr->Accept(*this);
    cout << " )";
}
void Dispatcher_pretty_print::Dispatch(ExpressionFunctionCall& z) {
    z.fcall->Accept(*this);
}
void Dispatcher_pretty_print::Dispatch(ExpressionIdentifier& z) {
    cout << z.id;
    if(z.posx) {
        cout<<"[ ";
        z.posx->Accept(*this);
        cout<<" ]";
    }
    if(z.posy) {
        cout<<"[ ";
        z.posy->Accept(*this);
        cout<<" ]";
    }
}
void Dispatcher_pretty_print::Dispatch(ExpressionLiteral& z) {
    z.expr->Accept(*this);
}
void Dispatcher_pretty_print::Dispatch(For_statement& z) {
    cout << "for ( ";
    if(z.decls) z.decls->Accept(*this);
    cout << " ; ";
    z.cond->Accept(*this);
    cout << " ; ";
    isFor = true;
    if(z.upd) z.upd->Accept(*this);
    isFor = false;
    cout << " ) ";
    z.block->Accept(*this);
}
void Dispatcher_pretty_print::Dispatch(Function_call& z) {
    cout << z.id << " ( ";
    z.p_list->Accept(*this);
    cout << " )";
}
void Dispatcher_pretty_print::Dispatch(Function_call_statement& z) {
    z.fcall->Accept(*this);
    cout<<";";
}
void Dispatcher_pretty_print::Dispatch(Function_decl& z) {
    cout << z.type << " " << z.id << " ( ";
    z.a_list->Accept(*this);
    cout << " ) ";
    z.blk->Accept(*this);
    cout<<"\n";
}
void Dispatcher_pretty_print::Dispatch(Function_list& z) {
    for(auto& y: z.decls) {
        y->Accept(*this);
        cout << "\n";
    }
}
void Dispatcher_pretty_print::Dispatch(If_statement& z) {
    if(z.cond) {
        cout<<"if ( ";
        z.cond->Accept(*this);
        cout << " ) ";
        z.block->Accept(*this);
        if(z.else_statement) {
            cout << "el";
            z.else_statement->Accept(*this);
        }
    }
    else {
        cout<<"se ";
        z.block->Accept(*this);
    }
}
void Dispatcher_pretty_print::Dispatch(IntegerLiteral& z) {
    cout << z.val;
}
void Dispatcher_pretty_print::Dispatch(Multivar_decl& z) {
    cout << z.decls[0]->type << " ";
    for (int i = 0; i < (int)z.decls.size(); ++i) {
        cout << z.decls[i]->id;
        if(z.decls[i]->shapex) {
            cout<<"["<<*(z.decls[i]->shapex)<<"]";
        }
        if(z.decls[i]->shapey) {
            cout<<"["<<*(z.decls[i]->shapey)<<"]";
        }
        if(z.decls[i]->initial_value) {
            cout<<" = ";
            z.decls[i]->initial_value->Accept(*this);
        }
        if(i != (int)z.decls.size() - 1) cout <<", ";
    }
}
void Dispatcher_pretty_print::Dispatch(Parameter_list& z) {
    for ( int i = 0; i < (int)z.parameters.size(); ++i ) {
        z.parameters[i]->Accept(*this);
        if(i != (int)z.parameters.size() - 1) cout << ", ";
    }
}
void Dispatcher_pretty_print::Dispatch(Program& z) {
    z.v_list->Accept(*this);
    z.f_list->Accept(*this);
}
void Dispatcher_pretty_print::Dispatch(Return_statement& z) {
    if(z.expr) {
        cout << "return ";
        z.expr->Accept(*this);
        cout<<";";
    }
    else {
        cout << "return;";
    }
}
void Dispatcher_pretty_print::Dispatch(Statement_list& z) {
    for(auto&y: z.statements) {
        for (int i = 0; i < tabs; i++) {
            cout<<"    ";
        }
        y->Accept(*this);
        cout << "\n";
    }
}
void Dispatcher_pretty_print::Dispatch(StringLiteral& z) {
    cout<<'\"';
    for(int i=1; i<(int)z.val.length() - 1; ++i) {
        if(z.val[i] == '\n') {
            cout << "\\n";
        }
        else if(z.val[i] == '\r') {
            cout << "\\r";
        }
        else if(z.val[i] == '\t') {
            cout << "\\t";
        }
        else if(z.val[i] == '\'') {
            cout << "\\\'";
        }
        else if(z.val[i] == '\"') {
            cout << "\\\"";
        }
        else if(z.val[i] == '\\') {
            cout << "\\\\";
        }
        else {
            cout << z.val[i];
        }
    }
    cout<<'\"';
}
void Dispatcher_pretty_print::Dispatch(Ternary_op& z) {
    z.cond->Accept(*this);
    cout << " ? ";
    z.exp1->Accept(*this);
    cout << " : ";
    z.exp2->Accept(*this);
}
void Dispatcher_pretty_print::Dispatch(Unary_op& z) {
    cout << z.op << " ";
    z.expr->Accept(*this);
}
void Dispatcher_pretty_print::Dispatch(UnsignedLiteral& z) {
    cout << z.val << "u";
}
void Dispatcher_pretty_print::Dispatch(Var_decl& z) {
    assert(0);
}
void Dispatcher_pretty_print::Dispatch(Variable_list& z) {
    for(auto& y: z.decls) {
        for (int i = 0; i < tabs; i++) {
            cout<<"    ";
        }
        y->Accept(*this);
        cout << ";\n";
    }
    if(z.decls.size()) cout << "\n";
}
void Dispatcher_pretty_print::Dispatch(While_statement& z) {
    cout << "while ( ";
    z.cond->Accept(*this);
    cout << " ) ";
    z.block->Accept(*this);
}