%{
#include <bits/stdc++.h>
#include "node.h"
#include "parser.tab.hh"
using namespace std;

extern "C" int yylex();
extern union node yylval;
int line_no = 1;
%}

COMMA ","
SEMICOLON ";"
QMARK "?"
COLON ":"

ASN "="
ADD "+"
SUB "-"
MUL "*"
DIV "/"
MOD "%"

LPAREN "("
RPAREN ")"
LBRACE "{"
RBRACE "}"
LSQUARE "["
RSQUARE "]"

OR "or"
AND "and"
NOT "not"
XOR "xor"
EQL "=="
NEQ "!="
LTE "<="
GTE ">="
LES "<"
GRE ">"

INT "int"
UNSIGNED "unsigned"
BOOL "bool"
CHAR "char"
VOID "void"

FOR "for"
WHILE "while"
IF "if"
ELIF "elif"
ELSE "else"

RETURN "return"

DIGIT [0-9]
ALPHA [a-zA-Z_]
ALPHANUM [0-9a-zA-Z_]
TRUE "true"
FALSE "false"
STR ([^\\"']|\\n|\\t|\\'|\\\\|\\\"|\\r)
UNSIGNED_SUFFIX [uU]

%%

{COMMA} 			 	 {return COMMA; }
{SEMICOLON} 			 {return SEMICOLON; }
{QMARK} 				 {return QMARK; }
{COLON} 				 {return COLON; }

{ASN} 					 {yylval.str_value = strdup(yytext); return ASN; }
{ADD} 					 {yylval.str_value = strdup(yytext); return ADD; }
{SUB} 					 {yylval.str_value = strdup(yytext); return SUB; }
{MUL} 					 {yylval.str_value = strdup(yytext); return MUL; }
{DIV} 					 {yylval.str_value = strdup(yytext); return DIV; }
{MOD} 					 {yylval.str_value = strdup(yytext); return MOD; }

{LPAREN}  				 {return LPAREN; }
{RPAREN}  				 {return RPAREN; }
{LBRACE}  				 {return LBRACE; }
{RBRACE}  				 {return RBRACE; }
{LSQUARE}  				 {return LSQUARE; }
{RSQUARE}  				 {return RSQUARE; }

{OR} 					 {yylval.str_value = strdup(yytext); return OR; }
{AND} 					 {yylval.str_value = strdup(yytext); return AND; }
{NOT} 					 {yylval.str_value = strdup(yytext); return NOT; }
{XOR} 					 {yylval.str_value = strdup(yytext); return XOR; }
{EQL}					 {yylval.str_value = strdup(yytext); return EQL; }
{NEQ}					 {yylval.str_value = strdup(yytext); return NEQ; }
{LTE}					 {yylval.str_value = strdup(yytext); return LTE; }
{GTE}					 {yylval.str_value = strdup(yytext); return GTE; }
{LES}					 {yylval.str_value = strdup(yytext); return LES; }
{GRE}					 {yylval.str_value = strdup(yytext); return GRE; }

{INT} 					 {yylval.str_value = strdup(yytext); return INT; }
{UNSIGNED} 				 {yylval.str_value = strdup(yytext); return UNSIGNED; }
{BOOL} 					 {yylval.str_value = strdup(yytext); return BOOL; }
{CHAR} 					 {yylval.str_value = strdup(yytext); return CHAR; }
{VOID} 					 {yylval.str_value = strdup(yytext); return VOID; }

{FOR} 					 {return FOR; }
{WHILE} 				 {return WHILE; }
{IF} 					 {return IF; }
{ELIF} 					 {return ELIF; }
{ELSE} 					 {return ELSE; }
{RETURN} 				 {return RETURN; }

{TRUE}|{FALSE}           {yylval.bool_value = (strcmp(yytext, "true") == 0); return BOOL_LITERAL; }
{DIGIT}+                 {yylval.int_value = atoi(yytext); return INT_LITERAL; }
{DIGIT}+{UNSIGNED_SUFFIX} {yylval.unsigned_value = atoi(yytext); return UNSIGNED_LITERAL; }
{ALPHA}{ALPHANUM}*       {yylval.str_value = strdup(yytext); return IDENTIFIER; }
\'{STR}\'                {
    if(yytext[1] != '\\') yylval.char_value = yytext[1];
    else if(yytext[2] == 'n') yylval.char_value = '\n';
    else if(yytext[2] == 't') yylval.char_value = '\t';
    else if(yytext[2] == '\'') yylval.char_value = '\'';
    else if(yytext[2] == '\\') yylval.char_value = '\\';
    else if(yytext[2] == '\"') yylval.char_value = '\"';
    else if(yytext[2] == 'r') yylval.char_value = '\r';
    else assert(0);
    return CHAR_LITERAL;
}
\"{STR}*\"               {yylval.str_value = strdup(yytext); return STRING_LITERAL; }

[ \t\v\r]+ 				 {/*whitespace*/}
\n                       {++line_no; }
%%