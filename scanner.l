/* scanner for a toy Pascal-like language */

%{
/* need this for the call to atof() below */
#include <bits/stdc++.h>
using namespace std;

extern "C" int yylex();
%}

DIGIT [0-9]
ID [a-zA-Z][A-Za-z0-9]*

%%

"-"?{DIGIT}+ {
	printf( "An integer literal: %s (%d)\n", yytext, atoi( yytext ) );
}

"-"{DIGIT}+"."{DIGIT}* {
	printf( "A float literal: %s (%g)\n", yytext, atof( yytext ) );
}

\'.\' {
	printf( "A character literal: %s (%c)\n", yytext, yytext[1] );
}

\".*\" {
	printf( "A string literal: %s (%s)\n", yytext, string(yytext).substr(1,strlen(yytext)-2).c_str() );
}

"true"|"false" {
	printf("A boolean literal: %s (%s)\n", yytext, yytext);
}

"+"|"-"|"*"|"/"|"and"|"or"|"not" printf( "An operator: %s\n", yytext );

if|else|for|while {
	printf( "A keyword: %s\n", yytext );
}

{ID} printf( "An identifier: %s\n", yytext );

[ \t\n]+ /* remove whitespace */

. printf( "Unrecognized character: %s\n", yytext );

%%

int main() {
	yylex();
}

