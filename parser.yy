%{
#include <bits/stdc++.h>
using namespace std;
#define YYDEBUG 1
extern "C" int yylex();
extern int yyparse();
extern int line_no;
void yyerror(const char *s);
%}

%token IDENTIFIER
%token INT_LITERAL
%token STRING_LITERAL
%token BOOL_LITERAL
%token CHAR_LITERAL
%token COMMA SEMICOLON
%token LPAREN RPAREN
%token LSQUARE RSQUARE
%token LBRACE RBRACE
%token IF ELSE ELIF FOR WHILE RETURN
%token INT BOOL VOID CHAR UNSIGNED

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

%start Program

%%
Program: VariableList FunctionList

VariableList: /*nothing*/ 
| VariableList MultipleVariable SEMICOLON 

FunctionList: /*nothing*/
| Function FunctionList

MultipleVariable: Variable 
| MultipleVariable COMMA IDENTIFIER ASN Expression 
| MultipleVariable COMMA IDENTIFIER 
| MultipleVariable COMMA IDENTIFIER LSQUARE INT_LITERAL RSQUARE  
| MultipleVariable COMMA IDENTIFIER LSQUARE INT_LITERAL RSQUARE  LSQUARE INT_LITERAL RSQUARE 

Datatype: INT
| CHAR
| BOOL
| UNSIGNED
| VOID

Variable: Datatype IDENTIFIER ASN Expression
| Datatype IDENTIFIER
| Datatype IDENTIFIER LSQUARE INT_LITERAL RSQUARE
| Datatype IDENTIFIER LSQUARE INT_LITERAL RSQUARE LSQUARE INT_LITERAL RSQUARE

Literal: CHAR_LITERAL
| INT_LITERAL
| BOOL_LITERAL
| STRING_LITERAL

Expression: Literal
| IDENTIFIER
| Expression ADD Expression
| Expression SUB Expression
| Expression MUL Expression
| Expression DIV Expression
| Expression MOD Expression
| Expression OR Expression
| Expression AND Expression
| Expression XOR Expression
| Expression EQL Expression
| Expression NEQ Expression
| Expression LTE Expression
| Expression GTE Expression
| Expression LES Expression
| Expression GRE Expression
| NOT Expression
| ADD Expression
| SUB Expression
| FunctionCall
| LPAREN Expression RPAREN
| Expression QMARK Expression COLON Expression
| IDENTIFIER LSQUARE Expression RSQUARE
| IDENTIFIER LSQUARE Expression RSQUARE LSQUARE Expression RSQUARE

FunctionCall: IDENTIFIER LPAREN ParameterList RPAREN

ParameterList: /*nothing*/
| Expression
| Expression COMMA ParameterList

Function: Datatype IDENTIFIER LPAREN ArgumentList RPAREN Block

Block: LBRACE VariableList StatementList RBRACE

ArgumentList: /*nothing*/
| Variable COMMA ArgumentList
| Variable

StatementList: /*nothing*/
| Statement StatementList

Statement: AssignmentStatement SEMICOLON
| FunctionCall SEMICOLON
| ReturnStatement
| ForStatement
| WhileStatement
| ifStatement
| Block

AssignmentStatement: IDENTIFIER ASN Expression
| IDENTIFIER LSQUARE Expression RSQUARE ASN Expression
| IDENTIFIER LSQUARE Expression RSQUARE LSQUARE Expression RSQUARE ASN Expression

ReturnStatement: RETURN Expression SEMICOLON 
| RETURN SEMICOLON

ForStatement: FOR LPAREN MultipleVariable SEMICOLON Expression SEMICOLON AssignmentStatement RPAREN Block
| FOR LPAREN SEMICOLON Expression SEMICOLON AssignmentStatement RPAREN Block
| FOR LPAREN MultipleVariable SEMICOLON Expression SEMICOLON RPAREN Block
| FOR LPAREN SEMICOLON Expression SEMICOLON RPAREN Block

WhileStatement: WHILE LPAREN Expression RPAREN Block

elifStatementList: /*nothing*/
| ELIF LPAREN Expression RPAREN Block elifStatementList
| ELSE Block

ifStatement: IF LPAREN Expression RPAREN Block elifStatementList

%%
int main(int argc, char **argv) {
    // yydebug = 1;
    yyparse();
}

void yyerror(const char *s) {
    cerr << "Syntax error on line " << line_no << ": " << s << endl;
}