%{
#include "a2.hh"
#include <ctype.h>
#include <string.h>
void yyerror (char *s);
int yylex();
%}

%%
("//"[^\n\r]*)								{;}
("/\*"([^\*]|(\*[^/]))*"\*/")				{;}
"int"|"float"|"void"						{yylval.id = strdup(yytext); return DATA_TYPE;}	
"if"										{yylval.id = strdup(yytext); return IF_TOK;}
"else"										{yylval.id = strdup(yytext); return ELSE_TOK;}
"while"										{yylval.id = strdup(yytext); return WHILE_TOK;}
"break"										{yylval.id = strdup(yytext); return BREAK_TOK;}
"continue"									{yylval.id = strdup(yytext); return CONTINUE_TOK;}
"return"									{yylval.id = strdup(yytext); return RETURN_TOK;}
"printf"									{yylval.id = strdup(yytext); return PRINTF_TOK;}
(\"%d\\n\")								{yylval.id = strdup(yytext); return FORMAT_SPECIFIER;}


"<="|">="|"<"|">"							{yylval.id = strdup(yytext); return REL_OP1;}
"=="|"!="									{yylval.id = strdup(yytext); return REL_OP2;}
"&&"										{yylval.id = strdup(yytext); return LOG_AND;}
"||"										{yylval.id = strdup(yytext); return LOG_OR;}
"!"|"&"										{yylval.id = strdup(yytext); return UNARY_OP;}
"/"|"%"										{yylval.id = strdup(yytext); return BINARY_OP;}

"+"|"-"										{yylval.id = strdup(yytext); return PLUSMIN;}
"*"											{yylval.id = strdup(yytext); return STAR;}
"="											{yylval.id = strdup(yytext); return ASS_OP;}

[a-zA-Z_][a-zA-Z0-9_]*			   			{yylval.id = strdup(yytext); return IDENTIFIER_TOK;}
[0-9]+										{yylval.id = strdup(yytext); return INT_LITERAL;} 
(([0-9]+"."[0-9]*)|("."[0-9]+)|([0-9]+))	{yylval.id = strdup(yytext); return	FLOAT_LITERAL;}

[ \t\n]                						{;}
.                      						{yylval.id = strdup(yytext); return yytext[0];}

%%
int yywrap (void) {return 1;}

