#include <bits/stdc++.h>
#include "dispatcher_visitor_test.h"

using namespace std;

void Dispatcher_visitor_test::Dispatch(Argument_list& z) {
    cout << "Visited Argument List\n";
    for(auto&y: z.arguments) {
        y->Accept(*this);
    }
}
void Dispatcher_visitor_test::Dispatch(Assignment_statement& z) {
    cout << "Visited Assignment Statement\n";
    if(z.posx) {
        z.posx->Accept(*this);
    }
    if(z.posy) {
        z.posy->Accept(*this);
    }
    z.expr->Accept(*this);
}
void Dispatcher_visitor_test::Dispatch(Binary_op& z) {
    cout << "Visited Binary operation\n";
    z.exp1->Accept(*this);
    z.exp2->Accept(*this);
}
void Dispatcher_visitor_test::Dispatch(Block& z) {
    cout << "Visited Block\n";
    z.v_list->Accept(*this);
    z.s_list->Accept(*this);
}
void Dispatcher_visitor_test::Dispatch(BlockStatement& z) {
    cout << "Visited Block Statement\n";
    z.block->Accept(*this);
}
void Dispatcher_visitor_test::Dispatch(BooleanLiteral& z) {
    cout << "Visited Boolean literal\n";
}
void Dispatcher_visitor_test::Dispatch(CharacterLiteral& z) {
    cout << "Visited Character Literal\n";
}
void Dispatcher_visitor_test::Dispatch(ExpressionBracketed& z) {
    cout << "Visited Bracketed Expression\n";
    z.expr->Accept(*this);
}
void Dispatcher_visitor_test::Dispatch(ExpressionFunctionCall& z) {
    cout << "Visited Function call expression\n";
    z.fcall->Accept(*this);
}
void Dispatcher_visitor_test::Dispatch(ExpressionIdentifier& z) {
    cout << "Visited Identifier Expression\n";
    if(z.posx) {
        z.posx->Accept(*this);
    }
    if(z.posy) {
        z.posy->Accept(*this);
    }
}
void Dispatcher_visitor_test::Dispatch(ExpressionLiteral& z) {
    cout << "Visited Literal Expression\n";
    z.expr->Accept(*this);
}
void Dispatcher_visitor_test::Dispatch(For_statement& z) {
    cout << "Visited For Statement\n";
    if(z.decls) z.decls->Accept(*this);
    z.cond->Accept(*this);
    if(z.upd) z.upd->Accept(*this);
    z.block->Accept(*this);
}
void Dispatcher_visitor_test::Dispatch(Function_call& z) {
    cout << "Visited Function call\n";
    z.p_list->Accept(*this);
}
void Dispatcher_visitor_test::Dispatch(Function_call_statement& z) {
    cout << "Visited Function call Statement\n";
    z.fcall->Accept(*this);
}
void Dispatcher_visitor_test::Dispatch(Function_decl& z) {
    cout << "Visited Function declaration\n";
    z.a_list->Accept(*this);
    z.blk->Accept(*this);
}
void Dispatcher_visitor_test::Dispatch(Function_list& z) {
    cout << "Visited Function List\n";
    for(auto& y: z.decls) {
        y->Accept(*this);
    }
}
void Dispatcher_visitor_test::Dispatch(If_statement& z) {
    cout << "Visited if/elif/else statement\n";
    if(z.cond) {
        z.cond->Accept(*this);
        z.block->Accept(*this);
        if(z.else_statement) {
            z.else_statement->Accept(*this);
        }
    }
    else {
        z.block->Accept(*this);
    }
}
void Dispatcher_visitor_test::Dispatch(IntegerLiteral& z) {
    cout << "Visited Integer Literal\n";
}
void Dispatcher_visitor_test::Dispatch(Multivar_decl& z) {
    cout << "Visited Multiple Variable declaration\n";
    for(auto&y: z.decls) {
        y->Accept(*this);
    }
}
void Dispatcher_visitor_test::Dispatch(Parameter_list& z) {
    cout << "Visited Parameter List\n";
    for ( int i = 0; i < (int)z.parameters.size(); ++i ) {
        z.parameters[i]->Accept(*this);
    }
}
void Dispatcher_visitor_test::Dispatch(Program& z) {
    cout << "Visited Program\n";
    z.v_list->Accept(*this);
    z.f_list->Accept(*this);
}
void Dispatcher_visitor_test::Dispatch(Return_statement& z) {
    cout << "Visited Return statement\n";
    if(z.expr) {
        z.expr->Accept(*this);
    }
}
void Dispatcher_visitor_test::Dispatch(Statement_list& z) {
    cout << "Visited Statement List\n";
    for(auto&y: z.statements) {
        y->Accept(*this);
    }
}
void Dispatcher_visitor_test::Dispatch(StringLiteral& z) {
    cout << "Visited String Literal\n";
}
void Dispatcher_visitor_test::Dispatch(Ternary_op& z) {
    cout << "Visited Ternary operator\n";
    z.cond->Accept(*this);
    z.exp1->Accept(*this);
    z.exp2->Accept(*this);
}
void Dispatcher_visitor_test::Dispatch(Unary_op& z) {
    cout << "Visited unary operation\n";
    z.expr->Accept(*this);
}
void Dispatcher_visitor_test::Dispatch(UnsignedLiteral& z) {
    cout << "Visited unsigned literal\n";
}
void Dispatcher_visitor_test::Dispatch(Var_decl& z) {
    cout << "Visited Variable declaration\n";
}
void Dispatcher_visitor_test::Dispatch(Variable_list& z) {
    cout << "Visited Variable List\n";
    for(auto& y: z.decls) {
        y->Accept(*this);
    }
}
void Dispatcher_visitor_test::Dispatch(While_statement& z) {
    cout << "Visited While statement\n";
    z.cond->Accept(*this);
    z.block->Accept(*this);
}