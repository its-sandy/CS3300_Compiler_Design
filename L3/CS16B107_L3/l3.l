%{
#include "l3.hh"
#include <ctype.h>
#include <string.h>

void yyerror (char *s);
int yylex();
%}

%option yylineno

%%

"int"						{return DATA_TYPE;}	

[a-zA-Z_][a-zA-Z0-9_]*		{yylval.id = strdup(yytext); return IDENTIFIER;}

[0-9]+						{yylval.num = atoi(yytext); return INT_LITERAL;}

[ \t\n]                		{;}

.                      		{return yytext[0];}

%%
int yywrap (void) {return 1;}

