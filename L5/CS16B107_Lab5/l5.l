%{
	// Example from http://epaperpress.com/lexandyacc/pry2.html
	#define YYSTYPE string
    #include <bits/stdc++.h>
    using namespace std;

    #include "y.tab.h"
%}

%%
[ \t\n]*				;
[a-z]					{yylval = string(yytext); return TERM;}
[A-Z][0-9a-zA-Z]*		{yylval = string(yytext); return NON_TERM;}
.						{return yytext[0];}
%%

int yywrap(void) {
    return 1;
}


