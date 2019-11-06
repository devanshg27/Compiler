#pragma once

#include "program.h"
#include "variable_list.h"
#include "function_list.h"
#include "variable.h"
#include "literal.h"
#include "expression.h"
#include "function_call.h"
#include "function_declaration.h"
#include "statement.h"
#include "statement_list.h"
#include "block.h"
#include "if_statement.h"
#include "loops.h"
#include "block_statement.h"
#include "function_call_statement.h"
#include "compound_expression.h"

union node {
    int int_value;
    char char_value;
    bool bool_value;
    char *str_value;

    class Program *program;
    class Variable_list *v_list;
    class Function_list *f_list;
    class Multivar_decl *multivar_decl;
    class Var_decl *var_decl;
    class Literal *literal;
    class Expression *expression;
    class Function_call *f_call;
    class Parameter_list *p_list;
    class Function_decl *function_decl;
    class Block *block;
    class Argument_list *arg_list;
    class Statement_list *s_list;
    class Statement *stmnt;
    class Assignment_statement *asgn_stmnt;
    class Return_statement *ret_stmnt;
    class For_statement *for_stmnt;
    class While_statement *while_stmnt;
    class If_statement *elif_stmnt;
    class If_statement *if_stmnt;

    node() = default;

    ~node() = default;
};

typedef union node YYSTYPE;