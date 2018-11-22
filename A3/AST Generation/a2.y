%{
	// Example from http://epaperpress.com/lexandyacc/pry2.html
	#include <bits/stdc++.h>
	using namespace std;

    struct node
    {
    	string name;
    	int num_child;
    	int longest_path;
    	int max_depth;
    	node* children[10];

    	node(string nname, int nnum_child)
    	{
    		name = nname;
    		num_child = nnum_child;
    		for(int i = 0; i<10; i++)
    			children[i] = NULL;
    	}
    };

    extern "C"
    {
    	int yylex(void);
    	int yywrap();
    }
    void dfs(node *,int);
    void yyerror(string);
    node* rootnode;
    set<int> nonterminalset;
    int maxwhilepath, maxprogpath, maxifpath, maxmainpath;
    extern int yydebug;
      
   	#define makeTree                                                \
   		do 															                              \
   		{ 														                               	\
   			node* temp;												                          \
   			node* ptr = new node(yytname[yyr1[yyn]], yyr2[yyn]);	      \
   			for(int i = 1; i<=yyr2[yyn]; i++) 					               	\
   			{ 														                              \
   				if(nonterminalset.find(yystos[yyssp[i-yyr2[yyn]]])==nonterminalset.end()) 				\
   					yyvsp[i-yyr2[yyn]].nnode = new node(yyvsp[i-yyr2[yyn]].id,0);		                \
   				temp = yyvsp[i-yyr2[yyn]].nnode;					                \
   				(ptr->children)[i] = temp; 							                  \
   			}														                                \
   			yyval.nnode = ptr; 										                      \
   		}while(0)

   	#define makeBinOpTree									            \
   		do 													                    \
   		{ 												                     	\
   			node* ptr = new node(yytname[yyr1[yyn]], 1);	\
   			node* temp = new node(yyvsp[2-3].id,2); 		  \
   			yyvsp[2-3].nnode = temp; 						          \
   			(ptr->children)[1] = temp; 					        	\
   			(temp->children)[1] = yyvsp[1-3].nnode; 	   	\
   			(temp->children)[2] = yyvsp[3-3].nnode; 	   	\
   															                      \
   			yyval.nnode = ptr; 						             		\
   		}while(0)

   	#define assignStmtTree 								           	\
   		do 													                    \
   		{ 												                     	\
   			node* ptr = new node(yytname[yyr1[yyn]], 2); 	\
   			node* temp = new node(yyvsp[2-4].id,2); 		  \
   			yyvsp[2-4].nnode = temp; 						          \
   			(ptr->children)[1] = temp; 						        \
   			(temp->children)[1] = yyvsp[1-4].nnode; 		  \
   			(temp->children)[2] = yyvsp[3-4].nnode; 		  \
   			temp = new node(yyvsp[4-4].id,0); 				    \
   			yyvsp[4-4].nnode = temp; 						          \
   			(ptr->children)[2] = temp; 					        	\
   														                       	\
   			yyval.nnode = ptr; 							            	\
   		}while(0)

   	#define assignArrayStmtTree 							        \
   		do 												                    	\
   		{											                       		\
   			node* ptr = new node(yytname[yyr1[yyn]], 2);	\
   			node* temp = new node(yyvsp[5-7].id,5);			  \
   			yyvsp[5-7].nnode = temp; 					          	\
   			(ptr->children)[1] = temp;						        \
   															                      \
   			(temp->children)[1] = yyvsp[1-7].nnode;			  \
   			node* temp2 = new node(yyvsp[2-7].id,0);		  \
   			yyvsp[2-7].nnode = temp2; 						        \
   			(temp->children)[2] = temp2;					        \
   			(temp->children)[3] = yyvsp[3-7].nnode; 			\
   			temp2 = new node(yyvsp[4-7].id,0);				    \
   			yyvsp[4-7].nnode = temp2; 						        \
   			(temp->children)[4] = temp2;					        \
   			(temp->children)[5] = yyvsp[6-7].nnode;			  \
   															                      \
   			temp = new node(yyvsp[7-7].id,0);				      \
   			yyvsp[7-7].nnode = temp; 						          \
   			(ptr->children)[2] = temp;						        \
   															                      \
   			yyval.nnode = ptr;								            \
   		}while(0)

%}

%union {struct node *nnode; char *id;}
%token-table
%start program
%token DATA_TYPE IF_TOK WHILE_TOK BREAK_TOK CONTINUE_TOK RETURN_TOK PRINTF_TOK ASS_OP IDENTIFIER_TOK INT_LITERAL FLOAT_LITERAL PLUSMIN STAR FORMAT_SPECIFIER
%nonassoc pexp
%nonassoc onlyif
%nonassoc ELSE_TOK
%left LOG_OR
%left LOG_AND
%left REL_OP2
%left REL_OP1
%left binplusmin
%left binstar BINARY_OP
%left UNARY_OP unplusmin unstar
%nonassoc array function

%%
program 	:	decl_list	{makeTree; rootnode = yyval.nnode;}
				  ;

decl_list :   decl_list	decl  {makeTree;}
    			|   decl 			      {makeTree;}
    			;

decl 		: 	var_decl 		{makeTree;}
				|   func_decl 	{makeTree;}
				;

var_decl 		:	type_spec identifier ';' 								              {makeTree;}
  				| 	type_spec identifier ',' var_decl 						        {makeTree;}
  				| 	type_spec identifier '[' integerLit ']' ';' 			    {makeTree;}
  				| 	type_spec identifier '[' integerLit ']' ',' var_decl 	{makeTree;}
  				;

type_spec : 	DATA_TYPE 		{makeTree;}
  				|	DATA_TYPE STAR 	{makeTree;}
  				;

func_decl : 	type_spec identifier '(' params ')' compound_stmt	{makeTree;}
				  ;

params 	: 	param_list 	{makeTree;}
				| 	epsilon		  {makeTree;}
				;

epsilon	:				{makeTree;}
				;

param_list 	: 	param_list ',' param  	{makeTree;}
    				|   param   				       {makeTree;}
    				;

param 			: 	type_spec identifier 			{makeTree;}
				| 	type_spec identifier '[' ']'	{makeTree;}
				;

stmt_list : 	stmt_list stmt 		{makeTree;}
  				| 	stmt 				      {makeTree;}
  				;

stmt 		: 	assign_stmt			{makeTree;} 
				| 	compound_stmt 	{makeTree;}
				| 	if_stmt 			  {makeTree;}
				| 	while_stmt			{makeTree;}
				| 	return_stmt 		{makeTree;}
				| 	break_stmt 			{makeTree;}
				| 	continue_stmt		{makeTree;}
        |   print_stmt      {makeTree;}
				;

print_stmt  :  PRINTF_TOK '(' FORMAT_SPECIFIER ',' identifier ')' ';' {makeTree;}
            ;

while_stmt 		: 	WHILE_TOK '(' expr ')' stmt 		{makeTree;}
				      ;

compound_stmt 	: 	'{' local_decls stmt_list '}'	{makeTree;}
				        ;

local_decls 	: 	local_decls local_decl   		{makeTree;}
				      | 	epsilon 						         {makeTree;}
			       	;

local_decl 	:	type_spec identifier ';' 				          {makeTree;}
				    | 	type_spec identifier '[' expr ']' ';' 	{makeTree;}
				    ;

if_stmt : 	IF_TOK '(' expr ')' stmt %prec onlyif	  {makeTree;}
				| 	IF_TOK '(' expr ')' stmt ELSE_TOK stmt 	{makeTree;}
				;

return_stmt : 	RETURN_TOK ';' 			  {makeTree;}
    				| 	RETURN_TOK expr ';'		{makeTree;}
    				;

break_stmt 	: 	BREAK_TOK ';'		{makeTree;}
				    ;

continue_stmt 	: 	CONTINUE_TOK ';'		{makeTree;}
				        ;	

assign_stmt 	: 	identifier ASS_OP expr ';'			       	{assignStmtTree;}
      				| 	identifier '[' expr ']' ASS_OP expr ';'	{assignArrayStmtTree;}
      				;

expr 		: 	Pexpr LOG_OR Pexpr						{makeBinOpTree;}
				| 	Pexpr LOG_AND Pexpr						{makeBinOpTree;}
				| 	Pexpr REL_OP2 Pexpr						{makeBinOpTree;}
				| 	Pexpr REL_OP1 Pexpr						{makeBinOpTree;}
				| 	Pexpr PLUSMIN Pexpr	%prec binplusmin	{makeBinOpTree;}
				| 	Pexpr STAR Pexpr	%prec binstar		     {makeBinOpTree;}
				| 	Pexpr BINARY_OP Pexpr					{makeBinOpTree;}
				| 	PLUSMIN Pexpr		%prec unplusmin		{makeTree;}
				| 	STAR Pexpr 			%prec unstar	  	{makeTree;}
				| 	UNARY_OP Pexpr							{makeTree;}
				| 	Pexpr				%prec pexp			{makeTree;}
				| 	identifier '(' args ')'	%prec function	{makeTree;}
				| 	identifier '[' expr ']'	%prec array		  {makeTree;}
				;

Pexpr 	: 	integerLit 		{makeTree;}
				| 	floatLit 		  {makeTree;}
				| 	identifier 		{makeTree;}
				| 	'(' expr ')'	{makeTree;}
				;

integerLit 	: 	INT_LITERAL		{makeTree;}
				    ;

floatLit 	: 	FLOAT_LITERAL	{makeTree;}
				  ;

identifier	: 	IDENTIFIER_TOK	{makeTree;}
				    ;

arg_list 	: 	arg_list ',' expr 	{makeTree;}
  				| 	expr				        {makeTree;}
  				;

args 		: 	arg_list 		{makeTree;}
				| 	epsilon			{makeTree;}
				;											


%%

void yyerror(string s) {
    fprintf(stdout, "Invalid\n");
}

int main(void) {

  yydebug = 1;
	for(int i = 1; i <= YYNRULES; i++)
		nonterminalset.insert(yyr1[i]);
    yyparse();

    maxwhilepath = maxprogpath = maxifpath = maxmainpath = 0;
    dfs(rootnode,0);
    // cout<<maxprogpath<<endl<<maxifpath<<endl<<maxwhilepath<<endl<<maxmainpath<<endl;
    return 0;
}

void dfs(node *root, int depth)
{
  cout<<root->name<<"\t"<<depth<<endl;
	if(root->num_child == 0)
	{
		root->max_depth = 0;
		root->longest_path = 0;
	}
	else
	{
		int max1 = -1, max2 = -1;
		root->longest_path = 0;

		for(int i=1; i<=root->num_child; i++)
		{
			dfs(root->children[i],depth+1);
			if(root->children[i]->max_depth >= max1)
			{
				max2 = max1;
				max1 = root->children[i]->max_depth;
			}
			else if(root->children[i]->max_depth >= max2)
				max2 = root->children[i]->max_depth;
			root->longest_path = max(root->longest_path, root->children[i]->longest_path);
		}
		root->max_depth = max1+1;
		root->longest_path = max(root->longest_path, max1+max2+2);
	}

	if(root->name == "if_stmt")
		maxifpath = max(maxifpath, root->longest_path);
	else if(root->name == "while_stmt")
		maxwhilepath = max(maxwhilepath, root->longest_path);
	else if(root->name == "program")
		maxprogpath = max(maxprogpath, root->longest_path);
	else if((root->name == "func_decl") && (root->children[2]->children[1]->name == "main"))
		maxmainpath = max(maxmainpath, root->longest_path);
}
