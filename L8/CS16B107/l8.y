%{
  #define YYSTYPE string
  #define pb push_back
	#include <bits/stdc++.h>
	using namespace std;

  int yylex(void);
  int yywrap(void);
  void yyerror(string);
  void print_output();

  unordered_map<string, int> complexity[2];
%}


%start program
%token INT_TOKEN VOID_TOKEN MAIN_TOKEN PRINTF_TOKEN FOR_TOKEN REL_OP INCREMENT MULDIV INT_LITERAL STRING_LITERAL IDENTIFIER

%%
program 	:	global_declarations main_function
				  ;

global_declarations : global_declarations decl;
                    |
                    ;

decl  : INT_TOKEN IDENTIFIER decl_helper ';'
      ;

decl_helper : decl_helper ',' IDENTIFIER
            |
            ;

main_function : VOID_TOKEN MAIN_TOKEN '(' ')' '{' outer_statements '}'

outer_statements  : outer_statements outer_statement
                  |
                  ;

outer_statement   : for_loop
                  {
                    print_output();
                    complexity[0].clear();
                    complexity[1].clear();
                  }
                  | print_statement
                  ;

statements  : statements print_statement
            | statements for_loop
            |
            ;

print_statement : PRINTF_TOKEN '(' STRING_LITERAL ')' ';'
                ;

for_loop  : FOR_TOKEN '(' INT_TOKEN IDENTIFIER '=' limits ';' IDENTIFIER REL_OP limits ';' proceed ')' '{' statements '}'
          {
            string str = max($6, $10);
            int t;
            if(($12) == "inc")
              t = 0;
            else
              t=1;

            if(complexity[t].find(str) == complexity[t].end())
              complexity[t][str] = 1;
            else
              complexity[t][str]++;
          }
          ;

limits  : INT_LITERAL   {$$ = string(" ");}
        | IDENTIFIER    {$$ = $1;}
        ;

proceed : IDENTIFIER INCREMENT            {$$ = string("inc");}
        | INCREMENT IDENTIFIER            {$$ = string("inc");}
        | IDENTIFIER MULDIV INT_LITERAL   {$$ = string("mul");}
        ;

%%

void yyerror(string s) {
    fprintf(stdout, "Invalid Syntax\n");
}

void print_output()
{
  if(complexity[0].find(string(" ")) != complexity[0].end())
    complexity[0].erase(string(" "));
  if(complexity[1].find(string(" ")) != complexity[1].end())
    complexity[1].erase(string(" "));

  if(complexity[0].size() + complexity[1].size() == 0)
    cout<<"1\n";
  else
  {
    vector<string> vstr;
    for(auto pp : complexity[0])
    {
      if(pp.second != 1)
        vstr.pb(pp.first + string("^") + to_string(pp.second));
      else
        vstr.pb(pp.first);
    }

    for(auto pp : complexity[1])
    {
      if(pp.second != 1)
        vstr.pb(string("log(") + pp.first + string(")^") + to_string(pp.second));
      else
        vstr.pb(string("log(") + pp.first + string(")"));
    }

    cout<<vstr[0];
    for(int i=1; i<vstr.size(); i++)
      cout<<"*"<<vstr[i];
    cout<<endl;
  }
}

int main(void) {

  // yydebug = 1;
  complexity[0].clear();
  complexity[1].clear();

	yyparse();
  return 0;
}