%{
#include <bits/stdc++.h>
#include "parser.tab.hh"
using namespace std;

extern "C" int yylex();
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
STR ([^\\"']|\\n|\\t|\\'|\\\\|\\\"|\\r|\\)

%%

{COMMA} 			 	 {return COMMA; }
{SEMICOLON} 			 {return SEMICOLON; }
{QMARK} 				 {return QMARK; }
{COLON} 				 {return COLON; }

{ASN} 					 {return ASN; }
{ADD} 					 {return ADD; }
{SUB} 					 {return SUB; }
{MUL} 					 {return MUL; }
{DIV} 					 {return DIV; }
{MOD} 					 {return MOD; }

{LPAREN}  				 {return LPAREN; }
{RPAREN}  				 {return RPAREN; }
{LBRACE}  				 {return LBRACE; }
{RBRACE}  				 {return RBRACE; }
{LSQUARE}  				 {return LSQUARE; }
{RSQUARE}  				 {return RSQUARE; }

{OR} 					 {return OR; }
{AND} 					 {return AND; }
{NOT} 					 {return NOT; }
{XOR} 					 {return XOR; }
{EQL}					 {return EQL; }
{NEQ}					 {return NEQ; }
{LTE}					 {return LTE; }
{GTE}					 {return GTE; }
{LES}					 {return LES; }
{GRE}					 {return GRE; }

{INT} 					 {return INT; }
{UNSIGNED} 				 {return UNSIGNED; }
{BOOL} 					 {return BOOL; }
{CHAR} 					 {return CHAR; }
{VOID} 					 {return VOID; }

{FOR} 					 {return FOR; }
{WHILE} 				 {return WHILE; }
{IF} 					 {return IF; }
{ELIF} 					 {return ELIF; }
{ELSE} 					 {return ELSE; }
{RETURN} 				 {return RETURN; }

{TRUE}|{FALSE}           {return BOOL_LITERAL; }
{DIGIT}+                 {return INT_LITERAL; }
{ALPHA}{ALPHANUM}*       {return IDENTIFIER; }
\'{STR}\'                {return CHAR_LITERAL; }
\"{STR}*\"               {return STRING_LITERAL; }

[ \t\v\r]+ 				 {/*whitespace*/}
\n                       {++line_no; }
%%