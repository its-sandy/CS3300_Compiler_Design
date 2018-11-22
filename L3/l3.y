%{

using namespace std;
extern "C"
{
    int yyparse(void);
    int yylex(void);  
    int yywrap();
}
extern int yylineno;
extern int yydebug;

#include <iostream>     /* C declarations used in actions */
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string>
#include <unordered_map>

void yyerror (string s);
void invalstmt (int lineno);
void divzeroerr (int lineno);
int yylex();

int errstatus;

unordered_map <string, int> symbolTable;
%}

/* Yacc definitions */
%union {int num; char *id;}
%start PROGRAM
%token DATA_TYPE
%token <id> IDENTIFIER
%token <num> INT_LITERAL

%type <num> EXPRESSION

%left '+' '-'
%left '*'
%left '/'

%%

/* descriptions of expected inputs     corresponding actions (in C) */
PROGRAM			:	PROGRAM DECLARATION 	{;}
				|	PROGRAM ASSIGNMENT		{;}
				|	PROGRAM EVALUATE 		{;}
				|							{;}
				;

DECLARATION 	:	DATA_TYPE IDENTIFIER ';'
					{
						if(symbolTable.find(string($2)) == symbolTable.end())
							symbolTable[string($2)] = INT_MAX;
						else
							invalstmt(yylineno);
					}
				;

ASSIGNMENT		:	IDENTIFIER '=' EXPRESSION ';'
					{
						if(symbolTable.find(string($1)) == symbolTable.end())
							errstatus = max(errstatus,2);

						if(errstatus == 0)
							symbolTable[string($1)] = $3;
						else if(errstatus == 1)
							divzeroerr(yylineno);
						else if(errstatus == 2)
							invalstmt(yylineno);
					}
				;

EVALUATE		:	EXPRESSION ';'	
					{
						if(errstatus == 0)
							cout<<($1)<<endl;
						else if(errstatus == 1)
							divzeroerr(yylineno);
						else if(errstatus == 2)
							invalstmt(yylineno);
					}
				;

EXPRESSION		:	'(' EXPRESSION ')'			{$$ = $2;}
				|	'+' EXPRESSION %prec '/'	{$$ = $2;}
				|	'-' EXPRESSION %prec '/'	{$$ = - $2;}
				|	EXPRESSION '+' EXPRESSION	{$$ = $1 + $3;}
				|	EXPRESSION '-' EXPRESSION	{$$ = $1 - $3;}
				|	EXPRESSION '*' EXPRESSION	{$$ = $1 * $3;}
				|	EXPRESSION '/' EXPRESSION	
					{
						if($3 != 0)
							$$ = $1 / $3;
						else
						{
							errstatus = max(errstatus,1);
							$$ = INT_MAX;
						}
					}
				|	IDENTIFIER
					{
						if(symbolTable.find(string($1)) == symbolTable.end() || symbolTable[string($1)] == INT_MAX)
						{
							errstatus = max(errstatus,2);
							$$ = INT_MAX;
						}
						else
							$$ = symbolTable[string($1)];
					}
				|	INT_LITERAL					{$$ = $1;}
				;


%%                     /* C code */


int main (void)
{
	// yydebug = 1;
	errstatus = 0;
	yyparse();
	return 0;
}

void yyerror (string s)
{
	cout<<"Invalid Input\n";
}

void invalstmt (int lineno)
{
	cout<<"Invalid Statement <"<<lineno<<">\n";
	exit(0);
}

void divzeroerr (int lineno)
{
	cout<<"Divide By Zero <"<<lineno<<">\n";
	exit(0);
}  