%{
#include <bits/stdc++.h>
#include "node.h"
#include "dispatcher_pretty_print.h"
#include "dispatcher_visitor_test.h"
#include "dispatcher_semantic_check.h"
#include "dispatcher_interpreter.h"
#include "dispatcher_llvm_gen.h"
using namespace std;
#define YYDEBUG 1
extern "C" int yylex();
extern "C" FILE *yyin;
extern int yyparse();
extern int line_no;
void yyerror(const char *s);
Program *root_node = NULL;
%}

%token <str_value> IDENTIFIER
%token <int_value> INT_LITERAL
%token <unsigned_value> UNSIGNED_LITERAL
%token <str_value> STRING_LITERAL
%token <bool_value> BOOL_LITERAL
%token <char_value> CHAR_LITERAL
%token COMMA SEMICOLON
%token LPAREN RPAREN
%token LSQUARE RSQUARE
%token LBRACE RBRACE
%token IF ELSE ELIF FOR WHILE RETURN
%token <str_value> INT BOOL VOID CHAR UNSIGNED

%token <str_value> ASN
%token <str_value> QMARK COLON
%token <str_value> OR
%token <str_value> XOR
%token <str_value> AND
%token <str_value> EQL NEQ
%token <str_value> LES GRE LTE GTE
%token <str_value> ADD SUB
%token <str_value> MUL DIV MOD
%token <str_value> NOT

%right ASN
%left QMARK COLON
%left OR
%left XOR
%left AND
%left EQL NEQ
%left LES GRE LTE GTE
%left ADD SUB
%left MUL DIV MOD

%nonassoc NOT

%type <program> Program
%type <v_list> VariableList
%type <f_list> FunctionList
%type <multivar_decl> MultipleVariable
%type <str_value> Datatype
%type <var_decl> Variable
%type <literal> Literal
%type <expression> Expression
%type <f_call> FunctionCall
%type <p_list> ParameterList
%type <function_decl> Function
%type <block> Block
%type <arg_list> ArgumentList
%type <s_list> StatementList
%type <stmnt> Statement
%type <asgn_stmnt> AssignmentStatement
%type <ret_stmnt> ReturnStatement
%type <for_stmnt> ForStatement
%type <while_stmnt> WhileStatement
%type <elif_stmnt> elifStatementList
%type <if_stmnt> ifStatement

%start Program

%%
Program: VariableList FunctionList {
    $$ = new Program($1, $2);
    root_node = $$;
}

VariableList: /*nothing*/                   { $$ = new Variable_list(); }
| VariableList MultipleVariable SEMICOLON   { $$->add_multivar_decl($2); }

FunctionList: /*nothing*/           { $$ = new Function_list(); }
| Function FunctionList             { $$ = $2; $$->add_function_decl($1); }

MultipleVariable: Variable { $$ = new Multivar_decl($1); }
| MultipleVariable COMMA IDENTIFIER ASN Expression { $$->add_var_decl(string($3), $5); }
| MultipleVariable COMMA IDENTIFIER { $$->add_var_decl(string($3), NULL); }
| MultipleVariable COMMA IDENTIFIER LSQUARE INT_LITERAL RSQUARE { $$->add_var_decl(string($3), $5, NULL); }
| MultipleVariable COMMA IDENTIFIER LSQUARE INT_LITERAL RSQUARE LSQUARE INT_LITERAL RSQUARE { $$->add_var_decl(string($3), $5, $8, NULL); }

Datatype: INT           { $$ = $1; }
| CHAR                  { $$ = $1; }
| BOOL                  { $$ = $1; }
| UNSIGNED              { $$ = $1; }
| VOID                  { $$ = $1; }

Variable: Datatype IDENTIFIER ASN Expression { $$ = new Var_decl(string($1), string($2), $4); }
| Datatype IDENTIFIER { $$ = new Var_decl(string($1), string($2), NULL); }
| Datatype IDENTIFIER LSQUARE INT_LITERAL RSQUARE { $$ = new Var_decl(string($1), string($2), $4, NULL); }
| Datatype IDENTIFIER LSQUARE INT_LITERAL RSQUARE LSQUARE INT_LITERAL RSQUARE { $$ = new Var_decl(string($1), string($2), $4, $7, NULL); }

Literal: CHAR_LITERAL   { $$ = new CharacterLiteral($1); }
| INT_LITERAL           { $$ = new IntegerLiteral($1); }
| UNSIGNED_LITERAL      { $$ = new UnsignedLiteral($1); }
| BOOL_LITERAL          { $$ = new BooleanLiteral($1); }
| STRING_LITERAL        { $$ = new StringLiteral(string($1)); }

Expression: Literal             { $$ = new ExpressionLiteral($1); }
| IDENTIFIER                    { $$ = new ExpressionIdentifier(string($1)); }
| Expression ADD Expression     { $$ = new Binary_op($1, string($2), $3); }
| Expression SUB Expression     { $$ = new Binary_op($1, string($2), $3); }
| Expression MUL Expression     { $$ = new Binary_op($1, string($2), $3); }
| Expression DIV Expression     { $$ = new Binary_op($1, string($2), $3); }
| Expression MOD Expression     { $$ = new Binary_op($1, string($2), $3); }
| Expression OR Expression      { $$ = new Binary_op($1, string($2), $3); }
| Expression AND Expression     { $$ = new Binary_op($1, string($2), $3); }
| Expression XOR Expression     { $$ = new Binary_op($1, string($2), $3); }
| Expression EQL Expression     { $$ = new Binary_op($1, string($2), $3); }
| Expression NEQ Expression     { $$ = new Binary_op($1, string($2), $3); }
| Expression LTE Expression     { $$ = new Binary_op($1, string($2), $3); }
| Expression GTE Expression     { $$ = new Binary_op($1, string($2), $3); }
| Expression LES Expression     { $$ = new Binary_op($1, string($2), $3); }
| Expression GRE Expression     { $$ = new Binary_op($1, string($2), $3); }
| NOT Expression                { $$ = new Unary_op(string($1), $2); }
| ADD Expression                { $$ = new Unary_op(string($1), $2); }
| SUB Expression                { $$ = new Unary_op(string($1), $2); }
| FunctionCall                  { $$ = new ExpressionFunctionCall($1); }
| LPAREN Expression RPAREN      { $$ = new ExpressionBracketed($2); }
| Expression QMARK Expression COLON Expression { $$ = new Ternary_op($1,$3,$5); }
| IDENTIFIER LSQUARE Expression RSQUARE { $$ = new ExpressionIdentifier(string($1), $3); }
| IDENTIFIER LSQUARE Expression RSQUARE LSQUARE Expression RSQUARE { $$ = new ExpressionIdentifier(string($1), $3, $6); }

FunctionCall: IDENTIFIER LPAREN ParameterList RPAREN {
    $$ = new Function_call($1, $3);
}

ParameterList: /*nothing*/              { $$ = new Parameter_list(); }
| Expression                            { $$ = new Parameter_list(); $$->add_parameter($1); }
| Expression COMMA ParameterList        { $$ = $3; $$->add_parameter($1); }

Function: Datatype IDENTIFIER LPAREN ArgumentList RPAREN Block {
    $$ = new Function_decl(string($1), string($2), $4, $6);
}

Block: LBRACE VariableList StatementList RBRACE {
    $$ = new Block($2, $3);
}

ArgumentList: /*nothing*/               { $$ = new Argument_list(); }
| Variable COMMA ArgumentList           { $$ = $3; $$->add_argument($1); }
| Variable                              { $$ = new Argument_list(); $$->add_argument($1); }

StatementList: /*nothing*/              { $$ = new Statement_list(); }
| Statement StatementList               { $$ = $2; $$->add_statement($1); }

Statement: AssignmentStatement SEMICOLON    { $$ = $1; }
| FunctionCall SEMICOLON                    { $$ = new Function_call_statement($1); }
| ReturnStatement                           { $$ = $1; }
| ForStatement                              { $$ = $1; }
| WhileStatement                            { $$ = $1; }
| ifStatement                               { $$ = $1; }
| Block                                     { $$ = new BlockStatement($1); }

AssignmentStatement: IDENTIFIER ASN Expression { $$ = new Assignment_statement(string($1), $3); }
| IDENTIFIER LSQUARE Expression RSQUARE ASN Expression { $$ = new Assignment_statement(string($1), $3, $6); }
| IDENTIFIER LSQUARE Expression RSQUARE LSQUARE Expression RSQUARE ASN Expression { $$ = new Assignment_statement(string($1), $3, $6, $9); }

ReturnStatement: RETURN Expression SEMICOLON        { $$ = new Return_statement($2); }
| RETURN SEMICOLON                                  { $$ = new Return_statement(NULL); }

ForStatement: FOR LPAREN MultipleVariable SEMICOLON Expression SEMICOLON AssignmentStatement RPAREN Block       { $$ = new For_statement($3, $5, $7, $9); }
| FOR LPAREN SEMICOLON Expression SEMICOLON AssignmentStatement RPAREN Block                                    { $$ = new For_statement(NULL, $4, $6, $8); }
| FOR LPAREN MultipleVariable SEMICOLON Expression SEMICOLON RPAREN Block                                       { $$ = new For_statement($3, $5, NULL, $8); }
| FOR LPAREN SEMICOLON Expression SEMICOLON RPAREN Block                                                        { $$ = new For_statement(NULL, $4, NULL, $7); }

WhileStatement: WHILE LPAREN Expression RPAREN Block                    { $$ = new While_statement($3, $5); }

elifStatementList: /*nothing*/                                          { $$ = NULL; }
| ELIF LPAREN Expression RPAREN Block elifStatementList                 { $$ = new If_statement($3, $5, $6); }
| ELSE Block                                                            { $$ = new If_statement(NULL, $2, NULL); }

ifStatement: IF LPAREN Expression RPAREN Block elifStatementList {
    $$ = new If_statement($3, $5, $6);
}

%%
int main(int argc, char **argv) {
    // yydebug = 1;
    if(argc == 1 or (argc == 2 and strcmp(argv[1], "--help")==0)) {
        cout << "Usage:\n";
        cout << "./cpl_parser / ./cpl_parser --help: Displays this help and exit\n";
        cout << "./cpl_parser <input_program_filename>: Interprets the program\n";
        cout << "./cpl_parser <input_program_filename> --stdout: Compiles the program to LLVM bytecode and prints the result to stdout\n";
        cout << "./cpl_parser <input_program_filename> <output_filename>: Compiles the program to LLVM bytecode and stores it in the output file\n";
        exit(0);
    }
    if(argc >= 2) {
        yyin = fopen(argv[1], "r");
    }
    yyparse();
    Dispatcher_semantic_check semantic_checker;
    root_node->Accept(semantic_checker);
    // Dispatcher_visitor_test visitor_test;
    // root_node->Accept(visitor_test);
    Dispatcher_pretty_print pretty_printer;
    root_node->Accept(pretty_printer);
    Dispatcher_interpreter interpreter;
    if(argc == 2) root_node->Accept(interpreter);
    Dispatcher_llvm_gen llvm_generator;
    root_node->Accept(llvm_generator);
    if(argc == 3) {
        if(llvm_generator.ret) {
            if(strcmp(argv[2], "--stdout")) llvm_generator.codeout(argv[2]);
            else llvm_generator.codeout();
        }
        else {
            cerr << "LLVM could not be generated.";
        }
    }
}

void yyerror(const char *s) {
    cerr << "Syntax error on line " << line_no << ": " << s << endl;
    exit(0);
}