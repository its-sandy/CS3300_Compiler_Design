%{
	// Example from http://epaperpress.com/lexandyacc/pry2.html
	#include <bits/stdc++.h>
	using namespace std;

		struct node
		{
			string name;
			int num_child;
			node* children[10];
			string datatype;

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
		void dfstranslate(node *);
		void yyerror(string);
		void paramDFS(node *);
		void funDeclNameFinder(node *);
		void funCallNameFinder(node *);

		node* rootnode;
		set<int> nonterminalset;
		extern int yydebug;

		map<string,int> functionSymbolTable;
		set<string> localFloat;
		set<string> globalFloat;

		map<string,int> argsSize;
		map<string,string> funReturnType;
		int labelInd;
		int stackLoc,stackLoc2;
		int curArgsSize;
		int RSPmaintenance;
		string returnLabel;
		string funNameAdder, funname, funCallNameAdder;
		string getNextLabel();
			
		#define makeTree                                                \
			do                                                            \
			{                                                             \
				node* temp;                                                 \
				node* ptr = new node(yytname[yyr1[yyn]], yyr2[yyn]);        \
				for(int i = 1; i<=yyr2[yyn]; i++)                           \
				{                                                           \
					if(nonterminalset.find(yystos[yyssp[i-yyr2[yyn]]])==nonterminalset.end())         \
						yyvsp[i-yyr2[yyn]].nnode = new node(yyvsp[i-yyr2[yyn]].id,0);                   \
					temp = yyvsp[i-yyr2[yyn]].nnode;                          \
					(ptr->children)[i] = temp;                                \
				}                                                           \
				yyval.nnode = ptr;                                          \
			}while(0)

		#define makeBinOpTree                             \
			do                                              \
			{                                               \
				node* ptr = new node(yytname[yyr1[yyn]], 1);  \
				node* temp = new node(yyvsp[2-3].id,2);       \
				yyvsp[2-3].nnode = temp;                      \
				(ptr->children)[1] = temp;                    \
				(temp->children)[1] = yyvsp[1-3].nnode;       \
				(temp->children)[2] = yyvsp[3-3].nnode;       \
																											\
				yyval.nnode = ptr;                            \
			}while(0)

		#define assignStmtTree                            \
			do                                              \
			{                                               \
				node* ptr = new node(yytname[yyr1[yyn]], 2);  \
				node* temp = new node(yyvsp[2-4].id,2);       \
				yyvsp[2-4].nnode = temp;                      \
				(ptr->children)[1] = temp;                    \
				(temp->children)[1] = yyvsp[1-4].nnode;       \
				(temp->children)[2] = yyvsp[3-4].nnode;       \
				temp = new node(yyvsp[4-4].id,0);             \
				yyvsp[4-4].nnode = temp;                      \
				(ptr->children)[2] = temp;                    \
																											\
				yyval.nnode = ptr;                            \
			}while(0)

		#define assignArrayStmtTree                       \
			do                                              \
			{                                               \
				node* ptr = new node(yytname[yyr1[yyn]], 2);  \
				node* temp = new node(yyvsp[5-7].id,5);       \
				yyvsp[5-7].nnode = temp;                      \
				(ptr->children)[1] = temp;                    \
																											\
				(temp->children)[1] = yyvsp[1-7].nnode;       \
				node* temp2 = new node(yyvsp[2-7].id,0);      \
				yyvsp[2-7].nnode = temp2;                     \
				(temp->children)[2] = temp2;                  \
				(temp->children)[3] = yyvsp[3-7].nnode;       \
				temp2 = new node(yyvsp[4-7].id,0);            \
				yyvsp[4-7].nnode = temp2;                     \
				(temp->children)[4] = temp2;                  \
				(temp->children)[5] = yyvsp[6-7].nnode;       \
																											\
				temp = new node(yyvsp[7-7].id,0);             \
				yyvsp[7-7].nnode = temp;                      \
				(ptr->children)[2] = temp;                    \
																											\
				yyval.nnode = ptr;                            \
			}while(0)

%}

%union {struct node *nnode; char *id;}
%token-table
%start program
%token DATA_TYPE IF_TOK WHILE_TOK BREAK_TOK CONTINUE_TOK RETURN_TOK PRINTF_TOK ASS_OP IDENTIFIER_TOK INT_LITERAL FLOAT_LITERAL PLUSMIN STAR INT_FORMAT_SPECIFIER FLOAT_FORMAT_SPECIFIER
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
program   : decl_list {makeTree; rootnode = yyval.nnode;}
					;

decl_list :   decl_list decl  {makeTree;}
					|   decl            {makeTree;}
					;

decl    :   var_decl    {makeTree;}
				|   func_decl   {makeTree;}
				;

var_decl    : type_spec identifier ';'                              {makeTree;}
					|   type_spec identifier ',' var_decl                     {makeTree;}
					|   type_spec identifier '[' integerLit ']' ';'           {makeTree;}
					|   type_spec identifier '[' integerLit ']' ',' var_decl  {makeTree;}
					;

type_spec :   DATA_TYPE     {makeTree;}
					| DATA_TYPE STAR  {makeTree;}
					;

func_decl :   type_spec identifier '(' params ')' compound_stmt {makeTree;}
					;

params  :   param_list  {makeTree;}
				|   epsilon     {makeTree;}
				;

epsilon :       {makeTree;}
				;

param_list  :   param_list ',' param    {makeTree;}
						|   param                  {makeTree;}
						;

param       :   type_spec identifier      {makeTree;}
				|   type_spec identifier '[' ']'  {makeTree;}
				;

stmt_list :   stmt_list stmt    {makeTree;}
					|   stmt              {makeTree;}
					;

stmt    :   assign_stmt     {makeTree;} 
				|   compound_stmt   {makeTree;}
				|   if_stmt         {makeTree;}
				|   while_stmt      {makeTree;}
				|   return_stmt     {makeTree;}
				|   break_stmt      {makeTree;}
				|   continue_stmt   {makeTree;}
				|   print_stmt      {makeTree;}
				;

print_stmt  :  PRINTF_TOK '(' int_specifier ',' identifier ')' ';' {makeTree;}
						|  PRINTF_TOK '(' float_specifier ',' identifier ')' ';' {makeTree;}
						;

int_specifier :	INT_FORMAT_SPECIFIER	{makeTree;}
				;

float_specifier :	FLOAT_FORMAT_SPECIFIER	{makeTree;}
				;

while_stmt    :   WHILE_TOK '(' expr ')' stmt     {makeTree;}
							;

compound_stmt   :   '{' local_decls stmt_list '}' {makeTree;}
								;

local_decls   :   local_decls local_decl      {makeTree;}
							|   epsilon                      {makeTree;}
							;

local_decl  : type_spec identifier ';'                  {makeTree;}
						|   type_spec identifier '[' expr ']' ';'   {makeTree;}
						;

if_stmt :   IF_TOK '(' expr ')' stmt %prec onlyif   {makeTree;}
				|   IF_TOK '(' expr ')' stmt ELSE_TOK stmt  {makeTree;}
				;

return_stmt :   RETURN_TOK ';'        {makeTree;}
						|   RETURN_TOK expr ';'   {makeTree;}
						;

break_stmt  :   BREAK_TOK ';'   {makeTree;}
						;

continue_stmt   :   CONTINUE_TOK ';'    {makeTree;}
								; 

assign_stmt   :   identifier ASS_OP expr ';'              {assignStmtTree;}
							|   identifier '[' expr ']' ASS_OP expr ';' {assignArrayStmtTree;}
							;

expr    :   Pexpr LOG_OR Pexpr            {makeBinOpTree;}
				|   Pexpr LOG_AND Pexpr           {makeBinOpTree;}
				|   Pexpr REL_OP2 Pexpr           {makeBinOpTree;}
				|   Pexpr REL_OP1 Pexpr           {makeBinOpTree;}
				|   Pexpr PLUSMIN Pexpr %prec binplusmin  {makeBinOpTree;}
				|   Pexpr STAR Pexpr  %prec binstar        {makeBinOpTree;}
				|   Pexpr BINARY_OP Pexpr         {makeBinOpTree;}
				|   PLUSMIN Pexpr   %prec unplusmin   {makeTree;}
				|   STAR Pexpr      %prec unstar      {makeTree;}
				|   UNARY_OP Pexpr              {makeTree;}
				|   Pexpr       %prec pexp      {makeTree;}
				|   identifier '(' args ')' %prec function  {makeTree;}
				|   identifier '[' expr ']' %prec array     {makeTree;}
				;

Pexpr   :   integerLit    {makeTree;}
				|   floatLit      {makeTree;}
				|   identifier    {makeTree;}
				|   '(' expr ')'  {makeTree;}
				;

integerLit  :   INT_LITERAL   {makeTree;}
						;

floatLit  :   FLOAT_LITERAL {makeTree;}
					;

identifier  :   IDENTIFIER_TOK  {makeTree;}
						;

arg_list  :   arg_list ',' expr   {makeTree;}
					|   expr                {makeTree;}
					;

args    :   arg_list    {makeTree;}
				|   epsilon     {makeTree;}
				;                     


%%

void yyerror(string s) {
		fprintf(stdout, "Invalid\n");
}

int main(void) {

	// yydebug = 1;
	RSPmaintenance = 0;
	for(int i = 1; i <= YYNRULES; i++)
		nonterminalset.insert(yyr1[i]);
	yyparse();

	//dfs(rootnode,0);
	//cout<<"\n-------------\n\n\n";
	labelInd = 0;
	dfstranslate(rootnode);
	return 0;
}

string getNextLabel()
{
	string label(".LF");
	label = label + to_string(labelInd);
	labelInd++;
	return label;
}

void dfs(node *root, int depth)
{
	cout<<root->name<<"\t"<<depth<<endl;

	for(int i=1; i<=root->num_child; i++)
		dfs(root->children[i],depth+1);
}

void dfstranslate(node* curnode)
{
	string nodeName = curnode->name;
	if(nodeName == "program")
	{
		cout<<"\t.file\t\"filename.c\"\n";
		cout<<"\t.section\t.rodata\n";
		cout<<".LC0:\n";
		cout<<"\t.string\t\"\%d\\n\"\n";
		cout<<".LC1:\n";
		cout<<"\t.string\t\"\%f\\n\"\n";
		cout<<"\t.text\n";
		cout<<"\t.comm\t"<<"rspsave"<<",8,8\n";
	}
	else if(nodeName == "var_decl")
	{
		string varname = ((curnode->children[2])->children[1])->name;
		string dtype = ((curnode->children[1])->children[1])->name;
		cout<<"\t.comm\t"<<varname<<",4,4\n";
		if(dtype == "float")
			globalFloat.insert(varname);
	}
	else if(nodeName == "func_decl")
	{
		functionSymbolTable.clear();
		localFloat.clear();
		stackLoc = 0;
		stackLoc2 = 8;
		curArgsSize = 0;
		returnLabel = "empty";

		funname = ((curnode->children[2])->children[1])->name;
		if(funname != "main")
		{
			funNameAdder = string("_");
			funDeclNameFinder(curnode->children[4]);
			funname = funname + funNameAdder;
		}

		funReturnType[funname] = curnode->children[1]->children[1]->name;		

		paramDFS(curnode->children[4]);
		argsSize[funname] = curArgsSize;

		cout<<"\t.globl\t"<<funname<<"\n";
		cout<<"\t.type\t"<<funname<<", @function\n";
		cout<<funname<<":\n";
		cout<<getNextLabel()<<":\n";
		cout<<"\t.cfi_startproc\n";
		cout<<"\tpushq \%rbp\n";
		cout<<"\t.cfi_def_cfa_offset 16\n";
		cout<<"\t.cfi_offset 6, -16\n";
		cout<<"\tmovq  \%rsp, \%rbp\n";
		cout<<"\t.cfi_def_cfa_register 6\n";
		// cout<<"\tsubq  $64, \%rsp\n";
		cout<<endl;
	}
	else if(nodeName == "local_decl")
	{
		string varname = ((curnode->children[2])->children[1])->name;
		string dtype = ((curnode->children[1])->children[1])->name;
		cout<<"\tsubq  $4, \%rsp\n";
		stackLoc-=4;
		functionSymbolTable[varname] = stackLoc;

		if(dtype == "float")
			localFloat.insert(varname);
	}
	else if(nodeName == "while_stmt")
	{
		string whileLabel1 = getNextLabel();
		string whileLabel2 = getNextLabel();

		cout<<"\tjmp\t"<<whileLabel1<<"\n";
		cout<<whileLabel2<<":\n";
		dfstranslate(curnode->children[5]);

		cout<<whileLabel1<<":\n";
		dfstranslate(curnode->children[3]);
		cout<<"\tpopq \%rax\n";
		cout<<"\tcmpl\t$0, \%eax\n";
		cout<<"\tjne\t"<<whileLabel2<<endl;
		cout<<endl;
	}
	else if(nodeName == "if_stmt")
	{
		if(curnode->num_child == 7)
		{
			string ifLabel1 = getNextLabel();
			string ifLabel2 = getNextLabel();

			dfstranslate(curnode->children[3]);
			cout<<"\tpopq \%rax\n";
			cout<<"\tcmpl\t$0, \%eax\n";
			cout<<"\tje\t"<<ifLabel1<<endl;
			dfstranslate(curnode->children[5]);
			cout<<"\tjmp\t"<<ifLabel2<<endl;
			cout<<ifLabel1<<":\n";
			dfstranslate(curnode->children[7]);
			cout<<ifLabel2<<":\n";
			cout<<endl;
		}
		else if(curnode->num_child == 5)
		{
			string ifLabel1 = getNextLabel();

			dfstranslate(curnode->children[3]);
			cout<<"\tpopq \%rax\n";
			cout<<"\tcmpl\t$0, \%eax\n";
			cout<<"\tje\t"<<ifLabel1<<endl;
			dfstranslate(curnode->children[5]);
			cout<<ifLabel1<<":\n";
			cout<<endl;
		}
	}

	/////////////
	if(nodeName != "while_stmt" && nodeName != "if_stmt")
	{
		for(int i=1; i<=curnode->num_child; i++)
			dfstranslate(curnode->children[i]);
	}
	/////////////

	if(nodeName == "Pexpr")
	{
		if(curnode->children[1]->name == "integerLit")
		{
			cout<<"\tmovl\t$"<< (curnode->children[1]->children[1]->name) <<", \%eax\n";
			cout<<"\tpushq\t\%rax\n";
			curnode->datatype = "int";
		}
		else if(curnode->children[1]->name == "floatLit")
		{
			float fnum = stof(curnode->children[1]->children[1]->name);
			char buffernum[20];
			sprintf(buffernum, "0x%x", *((unsigned int*)&fnum));
			string tempnum(buffernum);
			cout<<"\tmovl\t$"<< tempnum <<", \%eax\n";
			cout<<"\tpushq\t\%rax\n";
			curnode->datatype = "float";
		}
		else if(curnode->children[1]->name == "identifier")
		{

			string idf = curnode->children[1]->children[1]->name;
			if(functionSymbolTable.find(idf) == functionSymbolTable.end())
			{
				if(globalFloat.find(idf) == globalFloat.end())
				{
					curnode->datatype = "int";
					cout<<"\tmovl\t"<<idf<<"(\%rip), \%eax\n";
					cout<<"\tpushq\t\%rax\n";
				}
				else
				{
					curnode->datatype = "float";
					cout<<"\tmovss\t"<<idf<<"(\%rip), \%xmm0\n";
					cout<<"\tpushq\t\%rax\n";
					cout<<"\tmovss\t\%xmm0, (\%rsp)\n";
				}
			}
			else
			{
				if(localFloat.find(idf) == localFloat.end())
				{
					curnode->datatype = "int";
					cout<<"\tmovl\t"<< functionSymbolTable[idf] <<"(\%rbp), \%eax\n";
					cout<<"\tpushq\t\%rax\n";
				}
				else
				{
					curnode->datatype = "float";
					cout<<"\tmovss\t"<<functionSymbolTable[idf] <<"(\%rbp), \%xmm0\n";
					cout<<"\tpushq\t\%rax\n";
					cout<<"\tmovss\t\%xmm0, (\%rsp)\n";
				}				
			}
			cout<<endl;
		}
		else // ( expr )
		{
			curnode->datatype = curnode->children[2]->datatype;
		}
		cout<<endl;
	}
	if(nodeName == "expr")
	{
		if(curnode->num_child == 1 && curnode->children[1]->name != "Pexpr")
		{
			string op = curnode->children[1]->name;

			if(curnode->children[1]->children[1]->datatype == "int")
			{
				curnode->datatype = "int";
				if(op == "/" || op == "%")
				{
					cout<<"\tpopq\t\%rbx\n";
					cout<<"\tpopq\t\%rax\n";
				}
				else
				{
					cout<<"\tpopq\t\%rdx\n";
					cout<<"\tpopq\t\%rax\n";
				}

				if(op == "+")
					cout<<"\taddl\t\%edx, \%eax\n";
				else if(op == "-")
					cout<<"\tsubl\t\%edx, \%eax\n";
				else if(op == "*")
					cout<<"\timull\t\%edx, \%eax\n";
				else if(op == "/")
				{
					cout<<"\tcltd\n";
					cout<<"\tidivl\t\%ebx\n";
				}
				else if(op == "%")
				{
					cout<<"\tcltd\n";
					cout<<"\tidivl\t\%ebx\n";
				}
				else if(op == ">" || op == "<")
				{
					cout<<"\tcmpl\t\%edx, \%eax\n";
					if(op == ">")
						cout<<"\tsetg\t\%al\n";
					else if(op == "<")
						cout<<"\tsetl\t\%al\n";

					cout<<"\tmovzbl\t\%al, \%eax\n";
					cout<<"\tpushq\t\%rax\n";
				}

				if(op == "%")
					cout<<"\tpushq\t\%rdx\n";
				else if(op == "+" || op == "-" || op == "*" || op == "/")
					cout<<"\tpushq\t\%rax\n";

				cout<<endl;
			}
			else if(curnode->children[1]->children[1]->datatype == "float")
			{
				curnode->datatype = "float";
				cout<<"\tmovss\t(\%rsp), \%xmm1\n";
				cout<<"\tpopq\t\%rbx\n";
				cout<<"\tmovss\t(\%rsp), \%xmm0\n";
				cout<<"\tpopq\t\%rbx\n";

				if(op == "+")
				{
					cout<<"\taddss\t\%xmm1, \%xmm0\n";
					cout<<"\tpushq\t\%rbx\n";
					cout<<"\tmovss\t\%xmm0, \(%rsp)\n";
					
				}
				else if(op == "-")
				{
					cout<<"\tsubss\t\%xmm1, \%xmm0\n";
					cout<<"\tpushq\t\%rbx\n";
					cout<<"\tmovss\t\%xmm0, \(%rsp)\n";
				}
				else if(op == "*")
				{
					cout<<"\tmulss\t\%xmm1, \%xmm0\n";
					cout<<"\tpushq\t\%rbx\n";
					cout<<"\tmovss\t\%xmm0, \(%rsp)\n";
				}
				else if(op == "/")
				{
					cout<<"\tdivss\t\%xmm1, \%xmm0\n";
					cout<<"\tpushq\t\%rbx\n";
					cout<<"\tmovss\t\%xmm0, \(%rsp)\n";
				}
				else if(op == ">" || op == "<")
				{
					curnode->datatype = "int";
					if(op == ">")
						cout<<"\tucomiss\t\%xmm1, \%xmm0\n";
					else
						cout<<"\tucomiss\t\%xmm0, \%xmm1\n";
					cout<<"\tseta\t\%al\n";
					cout<<"\tmovzbl\t\%al, \%eax\n";
					cout<<"\tpushq\t\%rax\n";
				}

				cout<<endl;
			}	
		}
		else if(curnode->num_child == 1 && curnode->children[1]->name == "Pexpr")
		{
			curnode->datatype = curnode->children[1]->datatype;
		}
		else if(curnode->num_child == 4 && curnode->children[2]->name == "(")
		{
			string funCallName = curnode->children[1]->children[1]->name;
			funCallNameAdder = string("_");
			funCallNameFinder(curnode->children[3]);
			funCallName = funCallName + funCallNameAdder;

			cout<<"\tcall\t"<<funCallName<<endl;
			cout<<"\taddq  $"<<argsSize[funCallName]<<", \%rsp\n";
			cout<<"\tpushq\t\%rax\n";

			curnode->datatype = funReturnType[funCallName];
		}
	}
	else if(nodeName == "assign_stmt")
	{
		string idf = curnode->children[1]->children[1]->children[1]->name;

		if(functionSymbolTable.find(idf) == functionSymbolTable.end())
		{
			if(globalFloat.find(idf) == globalFloat.end())
			{
				cout<<"\tpopq\t\%rax\n";
				cout<<"\tmovl\t\%eax, "<<idf<<"(\%rip)\n";
			}
			else
			{
				cout<<"\tmovss\t(\%rsp), \%xmm0\n";
				cout<<"\tpopq\t\%rbx\n";
				cout<<"\tmovss\t\%xmm0, "<<idf<<"(\%rip)\n";
			}
		}	
		else
		{
			if(localFloat.find(idf) == localFloat.end())
			{
				cout<<"\tpopq\t\%rax\n";
				cout<<"\tmovl\t\%eax, "<< functionSymbolTable[idf] <<"(\%rbp)\n";
			}
			else
			{
				cout<<"\tmovss\t(\%rsp), \%xmm0\n";
				cout<<"\tpopq\t\%rbx\n";
				cout<<"\tmovss\t\%xmm0, "<< functionSymbolTable[idf] <<"(\%rbp)\n";
			}
		}

		cout<<endl;
	}
	else if(nodeName == "print_stmt")
	{
		string idf = curnode->children[5]->children[1]->name;

		if(curnode->children[3]->name == "int_specifier")
		{
			if(functionSymbolTable.find(idf) == functionSymbolTable.end())
				cout<<"\tmovl\t"<<idf<<"(\%rip), \%eax\n";
			else
				cout<<"\tmovl\t"<< functionSymbolTable[idf] <<"(\%rbp), \%eax\n";

			cout<<"\tmovl\t\%eax, \%esi\n";
			cout<<"\tmovl\t$.LC0, \%edi\n";
			cout<<"\tmovl\t$0, \%eax\n";
			cout<<"\tcall\tprintf\n";
			cout<<endl;
		}
		else if(curnode->children[3]->name == "float_specifier")
		{
			//rags: find last 4 bits by anding with 15 and then subtract this from rsp
			cout<<"\tmovq\t\%rsp, rspsave(\%rip)\n";
			cout<<"\tmovq\t\%rsp, \%rbx\n";
			cout<<"\tandq\t$15, \%rbx\n";
			cout<<"\tsubq\t\%rbx, \%rsp";
			cout<<endl;
			if(functionSymbolTable.find(idf) == functionSymbolTable.end())
				cout<<"\tcvtss2sd\t"<<idf<<"(\%rip), \%xmm0\n";
			else
				cout<<"\tcvtss2sd\t"<< functionSymbolTable[idf] <<"(\%rbp), \%xmm0\n";

			cout<<"\tmovl\t$.LC1, \%edi\n";
			cout<<"\tmovl\t$1, \%eax\n";
			cout<<"\tcall\tprintf\n";
			cout<<endl;
			cout<<"\tmovq\trspsave(\%rip), \%rsp\n";
		}
		cout<<endl;
	}
	else if(nodeName == "return_stmt")
	{
		if(curnode->num_child == 3)
			cout<<"\tpopq\t\%rax\n";

		if(returnLabel == "empty")
			returnLabel = getNextLabel();
		cout<<"\tjmp\t"<<returnLabel<<endl;
		cout<<endl;
	}
	else if(nodeName == "func_decl")
	{
		if(returnLabel == "empty")
			returnLabel = getNextLabel();

		cout<<returnLabel<<":\n";
		cout<<"\tleave\n";
		cout<<"\t.cfi_def_cfa 7, 8\n";
		cout<<"\tret\n";
		cout<<"\t.cfi_endproc\n";
		cout<<getNextLabel()<<":\n";
		cout<<"\t.size\t"<<funname<<", .-"<<funname<<endl;
		cout<<endl;
	}
}

void paramDFS(node* curnode)
{
	if(curnode->name == "param")
	{
		stackLoc2+=8;
		curArgsSize+=8;
		functionSymbolTable[curnode->children[2]->children[1]->name] = stackLoc2;

		if(curnode->children[1]->children[1]->name == "float")
			localFloat.insert(curnode->children[2]->children[1]->name);
	}
	for(int i=curnode->num_child; i>=1; i--)
		paramDFS(curnode->children[i]);
}

void funDeclNameFinder(node* curnode)
{
	if(curnode->name == "int")
		funNameAdder = funNameAdder + string("i");
	else if(curnode->name == "float")
		funNameAdder = funNameAdder + string("f");
	
	for(int i=1; i<=curnode->num_child; i++)
		funDeclNameFinder(curnode->children[i]);
}

void funCallNameFinder(node* curnode)
{
	if(curnode->name == "expr")
	{
		if(curnode->datatype == "int")
			funCallNameAdder = funCallNameAdder + string("i");
		else if(curnode->datatype == "float")
			funCallNameAdder = funCallNameAdder + string("f");
	}
	else
		for(int i=1; i<=curnode->num_child; i++)
			funCallNameFinder(curnode->children[i]);
}