%{
#define YYSTYPE string
#include <bits/stdc++.h>

using namespace std;
#include "y.tab.h"
%}

%%
("//"[^\n\r]*)					{;}
("/\*"([^\*]|(\*[^/]))*"\*/")	{;}
"int"							{return INT_TOKEN;}		
"void"							{return VOID_TOKEN;}
"main"							{return MAIN_TOKEN;}
"printf"						{return PRINTF_TOKEN;}
"for"							{return FOR_TOKEN;}	
">"|">="|"<"|"<="				{return REL_OP;}
"++"|"--"						{return INCREMENT;}
"/="|"*="						{return MULDIV;}

[0-9]+							{return INT_LITERAL;}
(\"(\\.|[^"\\])*\")				{return STRING_LITERAL;} 

[a-zA-Z_][a-zA-Z0-9_]*			{yylval = string(yytext); return IDENTIFIER;}

[ \t\n]               			{;}
.                     			{return yytext[0];}

%%
int yywrap (void) {return 1;}

