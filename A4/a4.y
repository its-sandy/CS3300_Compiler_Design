%{
  // Example from http://epaperpress.com/lexandyacc/pry2.html
  #include <bits/stdc++.h>
  using namespace std;

    struct node
    {
      string name;
      int num_child;
      int lineno;
      int staticvalue;
      string csestring;
      node* children[10];
      node* parent;

      bool isStrengthReduced;
      int preStrengthReducedValue;

      node(string nname, int nnum_child, int llineno)
      {
        name = nname;
        num_child = nnum_child;
        lineno = llineno;
        staticvalue = INT_MAX; // maintained only for expr and pexpr
        for(int i = 0; i<10; i++)
          children[i] = NULL;

        isStrengthReduced = false;
        preStrengthReducedValue = INT_MIN;
      }
    };

    extern "C"
    {
      int yylex(void);
      int yywrap();
    }

    extern int yylineno;
    
    void dfs(node *,int);
    void dfstranslate(node *);
    void dfsoptimize(node *, node *);
    void yyerror(string);
    void paramDFS(node *);
    void performOptimizations();
    void performTranslation();
    void getUnusedVars(node *);
    void getUnusedVarsWrapper();
    void getconstantFolding(node *);
    void getconstantFoldingWrapper();
    void getDeclarationOrder(node *);
    void getDeclarationOrderWrapper();
    void performCSE();
    void getCSEStrings(node *);
    void getNodeParents(node *, node *);
    bool isPowerOfTwo(int);
    int getLogTwo(int);

    node* rootnode;
    set<int> nonterminalset;
    extern int yydebug;
    ofstream assemblyFile;

    map<string,int> functionSymbolTable;
    map<string,int> functionSymbolValueTable;
    map<string,int> argsSize;
    vector<string> foldedOps;
    int labelInd;
    int stackLoc,stackLoc2;
    int curArgsSize;
    int declCount;
    int currentSection;
    string returnLabel;
    string getNextLabel();

    set<pair<int,string>> unusedVars;
    set<string> usedVars;
    int ifSimplification, ifStatementLineNo;
    int extraCSEVariables;
    map<int, int> strengthReductions;
    set<int> constantFoldedLines;
    map<int, int> constantFolding;
    map<int, set<pair<int, pair<string,int>>>> constantPropogations;
    map<string, int> declarationOrder;
    map<string, int> currentSSA, nextSSA;
    map<string, vector<pair<pair<int, int>, node*>>> CSEOccurrences;
    node* if_stmtNode;
    node* local_declsNode;
      
    #define makeTree                                                \
      do                                                            \
      {                                                             \
        node* temp;                                                 \
        node* ptr = new node(yytname[yyr1[yyn]], yyr2[yyn], yylineno);        \
        for(int i = 1; i<=yyr2[yyn]; i++)                           \
        {                                                           \
          if(nonterminalset.find(yystos[yyssp[i-yyr2[yyn]]])==nonterminalset.end())         \
            yyvsp[i-yyr2[yyn]].nnode = new node(yyvsp[i-yyr2[yyn]].id,0, yylineno);                   \
          temp = yyvsp[i-yyr2[yyn]].nnode;                          \
          (ptr->children)[i] = temp;                                \
        }                                                           \
        yyval.nnode = ptr;                                          \
      }while(0)

    #define makeBinOpTree                             \
      do                                              \
      {                                               \
        node* ptr = new node(yytname[yyr1[yyn]], 1, yylineno);  \
        node* temp = new node(yyvsp[2-3].id,2, yylineno);       \
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
        node* ptr = new node(yytname[yyr1[yyn]], 2, yylineno);  \
        node* temp = new node(yyvsp[2-4].id,2, yylineno);       \
        yyvsp[2-4].nnode = temp;                      \
        (ptr->children)[1] = temp;                    \
        (temp->children)[1] = yyvsp[1-4].nnode;       \
        (temp->children)[2] = yyvsp[3-4].nnode;       \
        temp = new node(yyvsp[4-4].id,0, yylineno);             \
        yyvsp[4-4].nnode = temp;                      \
        (ptr->children)[2] = temp;                    \
                                                      \
        yyval.nnode = ptr;                            \
      }while(0)

    #define assignArrayStmtTree                       \
      do                                              \
      {                                               \
        node* ptr = new node(yytname[yyr1[yyn]], 2, yylineno);  \
        node* temp = new node(yyvsp[5-7].id,5, yylineno);       \
        yyvsp[5-7].nnode = temp;                      \
        (ptr->children)[1] = temp;                    \
                                                      \
        (temp->children)[1] = yyvsp[1-7].nnode;       \
        node* temp2 = new node(yyvsp[2-7].id,0, yylineno);      \
        yyvsp[2-7].nnode = temp2;                     \
        (temp->children)[2] = temp2;                  \
        (temp->children)[3] = yyvsp[3-7].nnode;       \
        temp2 = new node(yyvsp[4-7].id,0, yylineno);            \
        yyvsp[4-7].nnode = temp2;                     \
        (temp->children)[4] = temp2;                  \
        (temp->children)[5] = yyvsp[6-7].nnode;       \
                                                      \
        temp = new node(yyvsp[7-7].id,0, yylineno);             \
        yyvsp[7-7].nnode = temp;                      \
        (ptr->children)[2] = temp;                    \
                                                      \
        yyval.nnode = ptr;                            \
      }while(0)

%}

%union {struct node *nnode; char *id;}
%token-table
%start program
%token DATA_TYPE IF_TOK WHILE_TOK BREAK_TOK CONTINUE_TOK RETURN_TOK PRINTF_TOK SCANF_TOK ASS_OP IDENTIFIER_TOK INT_LITERAL FLOAT_LITERAL PLUSMIN STAR PRINT_FORMAT_SPECIFIER SCAN_FORMAT_SPECIFIER
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
        |   scan_stmt       {makeTree;}
        ;

print_stmt  :  PRINTF_TOK '(' PRINT_FORMAT_SPECIFIER ',' identifier ')' ';' {makeTree;}
            ;

scan_stmt  :  SCANF_TOK '(' SCAN_FORMAT_SPECIFIER ',' UNARY_OP identifier ')' ';' {makeTree;}
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
  for(int i = 1; i <= YYNRULES; i++)
    nonterminalset.insert(yyr1[i]);
  yyparse();

  // dfs(rootnode,0);
  //cout<<"\n-------------\n\n\n";
  performOptimizations();
  performTranslation();

  return 0;
}

void performTranslation()
{
  assemblyFile.open("assembly.s");
  labelInd = 0;
  dfstranslate(rootnode);
  assemblyFile.close();
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
  cout<<root->name<<"\t"<<root->lineno<<endl;

  for(int i=1; i<=root->num_child; i++)
    dfs(root->children[i],depth+1);
}

void dfstranslate(node* curnode)
{
  string nodeName = curnode->name;
  if(nodeName == "program")
  {
    assemblyFile<<"\t.file\t\"filename.c\"\n";
    assemblyFile<<"\t.section\t.rodata\n";
    assemblyFile<<".LC0:\n";
    assemblyFile<<"\t.string\t\"\%d\\n\"\n";
    assemblyFile<<".LC1:\n";
    assemblyFile<<"\t.string\t\"\%d\"\n";
    assemblyFile<<"\t.text\n";
  }
  else if(nodeName == "var_decl")
  {
    string varname = ((curnode->children[2])->children[1])->name;
    assemblyFile<<"\t.comm\t"<<varname<<",4,4\n";
  }
  else if(nodeName == "func_decl")
  {
    functionSymbolTable.clear();
    stackLoc = 0;
    stackLoc2 = 8;
    curArgsSize = 0;
    returnLabel = "empty";
    string funname = ((curnode->children[2])->children[1])->name;

    paramDFS(curnode->children[4]);
    argsSize[funname] = curArgsSize;

    assemblyFile<<"\t.globl\t"<<funname<<"\n";
    assemblyFile<<"\t.type\t"<<funname<<", @function\n";
    assemblyFile<<funname<<":\n";
    assemblyFile<<getNextLabel()<<":\n";
    assemblyFile<<"\t.cfi_startproc\n";
    assemblyFile<<"\tpushq \%rbp\n";
    assemblyFile<<"\t.cfi_def_cfa_offset 16\n";
    assemblyFile<<"\t.cfi_offset 6, -16\n";
    assemblyFile<<"\tmovq  \%rsp, \%rbp\n";
    assemblyFile<<"\t.cfi_def_cfa_register 6\n";
    assemblyFile<<"\tsubq  $"<<4*(usedVars.size() + extraCSEVariables)<<", \%rsp\n";
    assemblyFile<<endl;
  }
  else if(nodeName == "local_decl")
  {
    string varname = ((curnode->children[2])->children[1])->name;
    //assemblyFile<<"\tsubq  $4, \%rsp\n";
    stackLoc-=4;
    functionSymbolTable[varname] = stackLoc;
  }
  else if(nodeName == "while_stmt")
  {
    string whileLabel1 = getNextLabel();
    string whileLabel2 = getNextLabel();

    assemblyFile<<"\tjmp\t"<<whileLabel1<<"\n";
    assemblyFile<<whileLabel2<<":\n";
    dfstranslate(curnode->children[5]);

    assemblyFile<<whileLabel1<<":\n";
    dfstranslate(curnode->children[3]);
    assemblyFile<<"\tpopq \%rax\n";
    assemblyFile<<"\tcmpl\t$0, \%eax\n";
    assemblyFile<<"\tjne\t"<<whileLabel2<<endl;
    assemblyFile<<endl;
  }
  else if(nodeName == "if_stmt")
  {
    if(curnode->num_child == 7)
    {
      string ifLabel1 = getNextLabel();
      string ifLabel2 = getNextLabel();

      dfstranslate(curnode->children[3]);
      assemblyFile<<"\tpopq \%rax\n";
      assemblyFile<<"\tcmpl\t$0, \%eax\n";
      assemblyFile<<"\tje\t"<<ifLabel1<<endl;
      dfstranslate(curnode->children[5]);
      assemblyFile<<"\tjmp\t"<<ifLabel2<<endl;
      assemblyFile<<ifLabel1<<":\n";
      dfstranslate(curnode->children[7]);
      assemblyFile<<ifLabel2<<":\n";
      assemblyFile<<endl;
    }
    else if(curnode->num_child == 5)
    {
      string ifLabel1 = getNextLabel();

      dfstranslate(curnode->children[3]);
      assemblyFile<<"\tpopq \%rax\n";
      assemblyFile<<"\tcmpl\t$0, \%eax\n";
      assemblyFile<<"\tje\t"<<ifLabel1<<endl;
      dfstranslate(curnode->children[5]);
      assemblyFile<<ifLabel1<<":\n";
      assemblyFile<<endl;
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
      assemblyFile<<"\tmovl\t$"<< (curnode->children[1]->children[1]->name) <<", \%eax\n";
      assemblyFile<<"\tpushq\t\%rax\n";
    }
    else if(curnode->children[1]->name == "identifier")
    {

      string idf = curnode->children[1]->children[1]->name;
      if(functionSymbolTable.find(idf) == functionSymbolTable.end())
        assemblyFile<<"\tmovl\t"<<idf<<"(\%rip), \%eax\n";
      else
        assemblyFile<<"\tmovl\t"<< functionSymbolTable[idf] <<"(\%rbp), \%eax\n";
      
      assemblyFile<<"\tpushq\t\%rax\n";
    }
    assemblyFile<<endl;
  }
  if(nodeName == "expr")
  {
    if(curnode->num_child == 1 && curnode->children[1]->name != "Pexpr")
    {
      string op = curnode->children[1]->name;

      if(op == "/" || op == "%")
      {
        assemblyFile<<"\tpopq\t\%rbx\n";
        assemblyFile<<"\tpopq\t\%rax\n";
      }
      else
      {
        assemblyFile<<"\tpopq\t\%rdx\n";
        assemblyFile<<"\tpopq\t\%rax\n";
      }

      if(op == "+")
        assemblyFile<<"\taddl\t\%edx, \%eax\n";
      else if(op == "-")
        assemblyFile<<"\tsubl\t\%edx, \%eax\n";
      else if(op == "*")
        assemblyFile<<"\timull\t\%edx, \%eax\n";
      else if(op == "/")
      {
        assemblyFile<<"\tcltd\n";
        assemblyFile<<"\tidivl\t\%ebx\n";
      }
      else if(op == "%")
      {
        assemblyFile<<"\tcltd\n";
        assemblyFile<<"\tidivl\t\%ebx\n";
      }
      else if(op == "<<")
      {
        assemblyFile<<"\tmovl\t\%eax, \%ecx\n";
        assemblyFile<<"\tsall\t\%cl, \%edx\n";
        assemblyFile<<"\tmovl\t\%edx, \%eax\n";
      }
      else if(op == "!=" || op == "==" || op == "<=" || op == ">=" || op == ">" || op == "<")
      {
        assemblyFile<<"\tcmpl\t\%edx, \%eax\n";
        if(op == "!=")
          assemblyFile<<"\tsetne\t\%al\n";
        else if(op == "==")
          assemblyFile<<"\tsete\t\%al\n";
        else if(op == ">=")
          assemblyFile<<"\tsetge\t\%al\n";
        else if(op == "<=")
          assemblyFile<<"\tsetle\t\%al\n";
        else if(op == ">")
          assemblyFile<<"\tsetg\t\%al\n";
        else if(op == "<")
          assemblyFile<<"\tsetl\t\%al\n";
        assemblyFile<<"\tmovzbl\t\%al, \%eax\n";
        assemblyFile<<"\tpushq\t\%rax\n";
      }
      else if(op == "&&")
      {
        string label1 = getNextLabel();
        string label2 = getNextLabel();

        assemblyFile<<"\tcmpl\t$0, \%eax\n";
        assemblyFile<<"\tje\t"<<label1<<endl;
        assemblyFile<<"\tcmpl\t$0, \%edx\n";
        assemblyFile<<"\tje\t"<<label1<<endl;
        assemblyFile<<"\tmovl\t$1, \%eax\n";
        assemblyFile<<"\tjmp\t"<<label2<<endl;
        assemblyFile<<label1<<":\n";
        assemblyFile<<"\tmovl\t$0, \%eax\n";
        assemblyFile<<label2<<":\n";
        assemblyFile<<"\tpushq\t\%rax\n";
      }
      else if(op == "||")
      {
        string label1 = getNextLabel();
        string label2 = getNextLabel();
        string label3 = getNextLabel();

        assemblyFile<<"\tcmpl\t$0, \%eax\n";
        assemblyFile<<"\tjne\t"<<label1<<endl;
        assemblyFile<<"\tcmpl\t$0, \%edx\n";
        assemblyFile<<"\tje\t"<<label2<<endl;
        assemblyFile<<label1<<":\n";
        assemblyFile<<"\tmovl\t$1, \%eax\n";
        assemblyFile<<"\tjmp\t"<<label3<<endl;
        assemblyFile<<label2<<":\n";
        assemblyFile<<"\tmovl\t$0, \%eax\n";
        assemblyFile<<label3<<":\n";
        assemblyFile<<"\tpushq\t\%rax\n";
      }

      if(op == "%")
        assemblyFile<<"\tpushq\t\%rdx\n";
      else if(op == "+" || op == "-" || op == "*" || op == "/" || op == "<<")
        assemblyFile<<"\tpushq\t\%rax\n";
      assemblyFile<<endl;
    }
    else if(curnode->num_child == 2)
    {
      string op = curnode->children[1]->name;

      if(op == "-")
      {
        assemblyFile<<"\tpopq\t\%rax\n";
        assemblyFile<<"\tnegl\t\%eax\n";
        assemblyFile<<"\tpushq\t\%rax\n";
      }
      else if(op == "!")
      {
        assemblyFile<<"\tpopq\t\%rax\n";
        assemblyFile<<"\tcmpl\t$0, \%eax\n";
        assemblyFile<<"\tsete\t\%al\n";
        assemblyFile<<"\tmovzbl\t\%al, \%eax\n";
        assemblyFile<<"\tpushq\t\%rax\n";
      }
      assemblyFile<<endl;
    }
    else if(curnode->num_child == 4 && curnode->children[2]->name == "(")
    {
      string funname = curnode->children[1]->children[1]->name;
      assemblyFile<<"\tcall\t"<<funname<<endl;
      assemblyFile<<"\taddq  $"<<argsSize[funname]<<", \%rsp\n";
      assemblyFile<<"\tpushq\t\%rax\n";
    }
  }
  else if(nodeName == "assign_stmt")
  {
    assemblyFile<<"\tpopq\t\%rax\n";
    string idf = curnode->children[1]->children[1]->children[1]->name;

    if(curnode->children[1]->num_child == 2)
    {
      if(functionSymbolTable.find(idf) == functionSymbolTable.end())
        assemblyFile<<"\tmovl\t\%eax, "<<idf<<"(\%rip)\n";
      else
        assemblyFile<<"\tmovl\t\%eax, "<< functionSymbolTable[idf] <<"(\%rbp)\n";
    }
    assemblyFile<<endl;
  }
  else if(nodeName == "print_stmt")
  {
    string idf = curnode->children[5]->children[1]->name;
    if(curnode->children[5]->name == "identifier")
    {
      if(functionSymbolTable.find(idf) == functionSymbolTable.end())
        assemblyFile<<"\tmovl\t"<<idf<<"(\%rip), \%eax\n";
      else
        assemblyFile<<"\tmovl\t"<< functionSymbolTable[idf] <<"(\%rbp), \%eax\n";

      assemblyFile<<"\tmovl\t\%eax, \%esi\n";
    }
    else if(curnode->children[5]->name == "integerLit")// print constant
      assemblyFile<<"\tmovl\t$"<<idf<<", \%esi\n";

    assemblyFile<<"\tmovl\t$.LC0, \%edi\n";
    assemblyFile<<"\tmovl\t$0, \%eax\n";
    assemblyFile<<"\tcall\tprintf\n";
    assemblyFile<<endl;
  }
  else if(nodeName == "scan_stmt")
  {
    string idf = curnode->children[6]->children[1]->name;
    if(functionSymbolTable.find(idf) == functionSymbolTable.end())
      assemblyFile<<"\tmovl\t$"<<idf<<", \%esi\n";
    else
    {
      assemblyFile<<"\tleaq\t"<< functionSymbolTable[idf] <<"(\%rbp), \%rax\n";
      assemblyFile<<"\tmovq\t\%rax, \%rsi\n";
    }

    assemblyFile<<"\tmovl\t$.LC1, \%edi\n";
    assemblyFile<<"\tmovl\t$0, \%eax\n";
    assemblyFile<<"\tcall\tscanf\n";
    assemblyFile<<endl;
  }
  else if(nodeName == "return_stmt")
  {
    if(curnode->num_child == 3)
      assemblyFile<<"\tpopq\t\%rax\n";

    if(returnLabel == "empty")
      returnLabel = getNextLabel();
    assemblyFile<<"\tjmp\t"<<returnLabel<<endl;
    assemblyFile<<endl;
  }
  else if(nodeName == "func_decl")
  {
    string funname = ((curnode->children[2])->children[1])->name;
    if(returnLabel == "empty")
      returnLabel = getNextLabel();

    assemblyFile<<returnLabel<<":\n";
    assemblyFile<<"\tleave\n";
    assemblyFile<<"\t.cfi_def_cfa 7, 8\n";
    assemblyFile<<"\tret\n";
    assemblyFile<<"\t.cfi_endproc\n";
    assemblyFile<<getNextLabel()<<":\n";
    assemblyFile<<"\t.size\t"<<funname<<", .-"<<funname<<endl;
    assemblyFile<<endl;
  }
}

void paramDFS(node* curnode)
{
  if(curnode->name == "param")
  {
    stackLoc2+=8;
    curArgsSize+=8;
    functionSymbolTable[curnode->children[2]->children[1]->name] = stackLoc2;
  }
  for(int i=curnode->num_child; i>=1; i--)
    paramDFS(curnode->children[i]);
}

void performOptimizations()
{
  foldedOps.push_back(string("+"));
  foldedOps.push_back(string("-"));
  foldedOps.push_back(string("*"));
  foldedOps.push_back(string("<"));
  foldedOps.push_back(string(">"));
  foldedOps.push_back(string("=="));
  foldedOps.push_back(string(">="));
  foldedOps.push_back(string("<="));
  foldedOps.push_back(string("!="));
  
  getDeclarationOrderWrapper(); // does even for unused variables

  ifSimplification = ifStatementLineNo = -1;
  functionSymbolValueTable.clear();
  constantFoldedLines.clear();

  dfsoptimize(rootnode, NULL);

  if(ifSimplification != -1)
    constantPropogations.erase(ifStatementLineNo);
  
  getconstantFoldingWrapper();

  getUnusedVarsWrapper(); // also removes from tree

  performCSE();

  ofstream sumFile;
  sumFile.open("summary.txt");

  sumFile<<"unused-vars\n";
  for(auto pp : unusedVars)
    sumFile<<pp.second<<endl;
  sumFile<<endl;

  sumFile<<"if-simpl\n";
  if(ifSimplification != -1)
    sumFile<<ifSimplification<<endl;
  sumFile<<endl;

  sumFile<<"strength-reduction\n";
  for(auto pp : strengthReductions)
    sumFile<<pp.first<<" "<<pp.second<<endl;
  sumFile<<endl;

  sumFile<<"constant-folding\n";
  for(auto pp : constantFolding)
    sumFile<<pp.first<<" "<<pp.second<<endl;
  sumFile<<endl;

  sumFile<<"constant-propagation\n";
  for(auto pp : constantPropogations)
  {
    //map<int, set<pair<int, pair<string,int>>>>
    sumFile<<pp.first;
    for(auto ppp : (pp.second))
      sumFile<<" "<<(ppp.second).first<<" "<<(ppp.second).second;
    sumFile<<endl;
  }
  sumFile<<endl;  

  // CSEOccurrences[curnode->csestring].push_back(make_pair(make_pair(currentSection, curnode->lineno), curnode));
  vector<vector<int>> CSEtemp;
  for(auto pp : CSEOccurrences)
  {
    vector<int> vt;
    for(auto ppp : (pp.second))
      vt.push_back((ppp.first).second);
    sort(vt.begin(), vt.end());
    CSEtemp.push_back(vt);
  }
  sort(CSEtemp.begin(), CSEtemp.end());

  sumFile<<"cse\n";
  for(auto vv : CSEtemp)
  {
    sumFile<<vv[0];
    for(int j=1; j<vv.size(); j++)
      sumFile<<" "<<vv[j];
    sumFile<<endl;
  }
}


void dfsoptimize(node* curnode, node* parent)
{
  string nodeName = curnode->name;

  if(nodeName == "if_stmt") // parent is stmt with 1 child
  {
    ifStatementLineNo = curnode->children[3]->lineno;
    dfsoptimize(curnode->children[3], curnode);

    if(curnode->children[3]->staticvalue != INT_MAX)
    {// statically evaluatable
      constantFoldedLines.erase(curnode->children[3]->lineno);
      if(curnode->children[3]->staticvalue != 0)
      {// true
        ifSimplification = 1;

        parent->children[1] = curnode->children[5]->children[1];
        curnode = parent->children[1];
      }
      else if(curnode->children[3]->staticvalue == 0)
      {// false
        ifSimplification = 0;

        if(curnode->num_child == 7)
        {// else available
          parent->children[1] = curnode->children[7]->children[1];
          curnode = parent->children[1];
        }
        else
        {// no else available
          curnode->name = string("dead_code");
          parent->num_child = 0;
          return;
        }
      }
      nodeName = curnode->name;
    }
    else
    {// not statically evaluatable
      map<string, int> symbolTableBackup, ifEndSymbolTable, elseEndSymbolTable;

      symbolTableBackup = functionSymbolValueTable;

      dfsoptimize(curnode->children[5], curnode);
      ifEndSymbolTable = functionSymbolValueTable;

      functionSymbolValueTable = symbolTableBackup;
      if(curnode->num_child == 7)
      {
        dfsoptimize(curnode->children[7], curnode);
        elseEndSymbolTable = functionSymbolValueTable;
      }
      else
        elseEndSymbolTable = functionSymbolValueTable;

      // merging the symbol tables
      functionSymbolValueTable = symbolTableBackup;
      for(auto pp : functionSymbolValueTable)
      {
        if(ifEndSymbolTable[pp.first] == elseEndSymbolTable[pp.first])
          functionSymbolValueTable[pp.first] = ifEndSymbolTable[pp.first];
        else
          functionSymbolValueTable[pp.first] = INT_MAX;
      }
    }
  }

  ////////////
  if(nodeName != "if_stmt") // handle this
  {
    for(int i=1; i<=curnode->num_child; i++)
      dfsoptimize(curnode->children[i], curnode); 
  }
  ////////////

  if(nodeName == "Pexpr")
  {
    curnode->staticvalue = INT_MAX;

    if(curnode->children[1]->name == "integerLit")
    {
      curnode->staticvalue = stoi(curnode->children[1]->children[1]->name);
    }
    else if(curnode->children[1]->name == "identifier")
    {
      string idf = curnode->children[1]->children[1]->name;
      int statval = functionSymbolValueTable[idf];

      if(statval != INT_MAX)
      {
        constantPropogations[curnode->lineno].insert(make_pair(declarationOrder[idf], make_pair(idf, statval)));
        curnode->staticvalue = statval;
        curnode->children[1]->name = "integerLit";
        curnode->children[1]->children[1]->name = to_string(statval);
      }
    }
    else if(curnode->num_child == 3 && curnode->children[2]->name == "expr")
    {
      // remember to update number of children and preserve form
      int statval = curnode->children[2]->staticvalue;

      if(statval != INT_MAX)
      {
        curnode->staticvalue = statval;
        curnode->num_child = 1;

        curnode->children[1] = curnode->children[2];
        curnode->children[1]->num_child = 1;
        curnode->children[1]->name = "integerLit";

        curnode->children[1]->children[1]->name = to_string(statval); // expr must have had at least one child
        curnode->children[1]->children[1]->num_child = 0;

      }
    }
  }
  else if(nodeName == "expr")
  {
    curnode->staticvalue = INT_MAX;

    if(curnode->num_child == 1 && curnode->children[1]->name == "Pexpr")
    {
      curnode->staticvalue = curnode->children[1]->staticvalue; // handles both cases
    }
    else if(curnode->num_child == 1) //binary operator
    {
      string op = curnode->children[1]->name;
      int val1 = curnode->children[1]->children[1]->staticvalue, val2 = curnode->children[1]->children[2]->staticvalue, calcval;

      if((val1 != INT_MAX) && (val2 != INT_MAX) && (find(foldedOps.begin(), foldedOps.end(), op) != foldedOps.end()))
      {
        // remember to manage folded operators in main
        constantFoldedLines.insert(curnode->lineno);
        if(op == "+")
          calcval = val1+val2;
        else if(op == "-")
          calcval = val1 - val2;
        else if(op == "*")
          calcval = val1*val2;
        else if(op == "/")
          calcval = val1/val2;
        else if(op == "%")
          calcval = val1%val2;
        else if(op == "&&")
          calcval = val1&&val2;
        else if(op == "||")
          calcval = val1||val2;
        else if(op == ">")
          calcval = val1>val2;
        else if(op == "<")
          calcval = val1<val2;
        else if(op == ">=")
          calcval = val1>=val2;
        else if(op == "<=")
          calcval = val1<=val2;
        else if(op == "==")
          calcval = val1==val2;
        else if(op == "!=")
          calcval = val1!=val2;

        // if Pexpr has good static value, it means it is only of type integerLit 
        curnode->children[1] = curnode->children[1]->children[1]; // Pexpr becomes child of expr
        curnode->staticvalue = curnode->children[1]->staticvalue = calcval;
        curnode->children[1]->children[1]->children[1]->name = to_string(calcval);
      }
      else if((op == "*") && (max(val1, val2) == INT_MAX) && isPowerOfTwo(min(val1, val2)))
      {// check if strength reduction is possible
        if(val1 == INT_MAX)
        {// second operand has to be the unknown
          node* temp = curnode->children[1]->children[1];
          curnode->children[1]->children[1] = curnode->children[1]->children[2];
          curnode->children[1]->children[2] = temp;
        }
        val1 = curnode->children[1]->children[1]->staticvalue;

        curnode->children[1]->children[1]->children[1]->children[1]->isStrengthReduced = true;
        curnode->children[1]->children[1]->children[1]->children[1]->preStrengthReducedValue = val1;

        val1 = getLogTwo(val1);
        strengthReductions[curnode->lineno] = max(strengthReductions[curnode->lineno], val1);

        curnode->children[1]->children[1]->staticvalue = val1;
        curnode->children[1]->children[1]->children[1]->children[1]->name = to_string(val1);

        curnode->children[1]->name = string("<<");
      } 
    }
    else if(curnode->num_child == 2) //binary operator
    {// unary operators should not be folded
      // string op = curnode->children[1]->name;
      // int val1 = curnode->children[2]->staticvalue, calcval;

      // if((val1 != INT_MAX) && (find(foldedOps.begin(), foldedOps.end(), op) != foldedOps.end()))
      // {
      //   // remember to manage folded operators in main
      //   if(op == "+")
      //     calcval = val1;
      //   else if(op == "-")
      //     calcval = -val1;
      //   else if(op == "!")
      //     calcval = !val1;
        
      //   // if Pexpr has good static value, it means it is only of type integerLit 
      //   curnode->num_child = 1;
      //   curnode->children[1] = curnode->children[2]; // Pexpr becomes child of expr
      //   curnode->staticvalue = curnode->children[1]->staticvalue = calcval;
      //   curnode->children[1]->children[1]->children[1]->name = to_string(calcval);
      // } 
    } 
  }
  else if(nodeName == "assign_stmt")
  {
    functionSymbolValueTable[curnode->children[1]->children[1]->children[1]->name] = curnode->children[1]->children[2]->staticvalue;    
  }
  else if(nodeName == "scan_stmt")
  {
    functionSymbolValueTable[curnode->children[6]->children[1]->name] = INT_MAX;
  }
  else if(nodeName == "var_decl")
  {
    functionSymbolValueTable[curnode->children[2]->children[1]->name] = INT_MAX;
  }
  else if(nodeName == "print_stmt")
  {
    string idf = curnode->children[5]->children[1]->name;
    int statval = functionSymbolValueTable[idf];
    if(statval != INT_MAX)
    {
      curnode->children[5]->name = "integerLit";
      curnode->children[5]->children[1]->name = to_string(statval);
      constantPropogations[curnode->lineno].insert(make_pair(declarationOrder[idf], make_pair(idf, statval)));
    }
  }
}

void getUnusedVarsWrapper()
{
  unusedVars.clear();
  usedVars.clear();
  getUnusedVars(rootnode);
}

void getUnusedVars(node* curnode)
{
  string nodeName = curnode->name;
  if(nodeName == "local_decl")
  {
    if(usedVars.find(curnode->children[2]->children[1]->name) == usedVars.end())
    {
      string idf = curnode->children[2]->children[1]->name;
      unusedVars.insert(make_pair(declarationOrder[idf], idf));
      curnode->name = "dead_code";
      curnode->num_child = 0;
    }
  }
  else if(nodeName == "assign_stmt")
    usedVars.insert(curnode->children[1]->children[1]->children[1]->name);
  else if(nodeName == "scan_stmt")
    usedVars.insert(curnode->children[6]->children[1]->name);
  else 
  {
    for(int i = curnode->num_child; i>=1; i--)
      getUnusedVars(curnode->children[i]);
  }
}

void getconstantFolding(node* curnode)
{
  if((curnode->name == "integerLit") && (constantFoldedLines.find(curnode->lineno) != constantFoldedLines.end()))
  {
    if(curnode->children[1]->isStrengthReduced == false)
      constantFolding[curnode->lineno] = max(constantFolding[curnode->lineno], stoi(curnode->children[1]->name));
    else
      constantFolding[curnode->lineno] = max(constantFolding[curnode->lineno], curnode->children[1]->preStrengthReducedValue);
  }

  for(int i=1; i<=curnode->num_child; i++)
    getconstantFolding(curnode->children[i]);
}

void getconstantFoldingWrapper()
{
  for(auto l : constantFoldedLines)
    constantFolding[l] = INT_MIN;
  getconstantFolding(rootnode);
}

void getDeclarationOrder(node* curnode)
{
  if(curnode->name == "local_decl")
  {
    declCount++;
    declarationOrder[curnode->children[2]->children[1]->name] = declCount;
  }

  for(int i=1; i<=curnode->num_child; i++)
    getDeclarationOrder(curnode->children[i]);
}

void getDeclarationOrderWrapper()
{// should be done before dfsOptimize
  declCount = 0;
  getDeclarationOrder(rootnode);
}

bool isPowerOfTwo(int x) 
{ 
  if(x == INT_MAX)
    return false;
  /* First x in the below expression is for the case when x is 0 */
  return x && (!(x&(x-1))); 
} 

int getLogTwo(int x)
{
  int val = 0;
  while(x >>= 1) ++val;
  return val;
}

void performCSE()
{
  // map<string, vector<pair<pair<int, int>, node*>>> CSEOccurrences; //CSEstring, section number, line number, node
  for(auto idf : usedVars)
  {
    currentSSA[idf] = 0;
    nextSSA[idf] = 1;
  }

  currentSection = 1; // 1- before ifelse, 2- if, 3- else, 4- after ifelse
  getCSEStrings(rootnode);

  local_declsNode = NULL;
  getNodeParents(rootnode, NULL);

  // now we have if_stmtNode, first local_decls node and parents of all nodes

  map<string, vector<pair<pair<int, int>, node*>>> tempCSEOccurrences;
  tempCSEOccurrences = CSEOccurrences;
  CSEOccurrences.clear();
  for(auto pp : tempCSEOccurrences)
  {
    if((pp.second).size() >= 2)
    {
      vector<pair<pair<int, int>, node*>> vt;
      vt = pp.second;
      sort(vt.begin(), vt.end());
      CSEOccurrences[pp.first] = vt;
    }
  }
  
  // change tree according to the CSEs , do rans error correction
  extraCSEVariables = CSEOccurrences.size();
}

void getCSEStrings(node* curnode)
{
  string nodeName = curnode->name;
  if(nodeName == "if_stmt")
  {
    getCSEStrings(curnode->children[3]);

    map<string, int> currentSSABackup, ifCurrentSSA, elseCurrentSSA;
    currentSSABackup = currentSSA;

    currentSection = 2;
    getCSEStrings(curnode->children[5]);
    ifCurrentSSA = currentSSA;

    currentSSA = currentSSABackup;
    currentSection = 3;
    if(curnode->num_child == 7)
    {
      getCSEStrings(curnode->children[7]);
      elseCurrentSSA = currentSSA;
    }
    else
      elseCurrentSSA = currentSSA;

    currentSSA = currentSSABackup;

    for(auto pp : currentSSA)
    {
      if(ifCurrentSSA[pp.first] == elseCurrentSSA[pp.first])
      {
        currentSSA[pp.first] = ifCurrentSSA[pp.first];
        nextSSA[pp.first] = ifCurrentSSA[pp.first] + 1;
      }
      else
      {
        currentSSA[pp.first] = nextSSA[pp.first];
        nextSSA[pp.first] = nextSSA[pp.first] + 1;
      }
    }
    currentSection = 4;
  }
  else
  {
    for(int i=1; i<=curnode->num_child; i++)
      getCSEStrings(curnode->children[i]);

    if(nodeName == "Pexpr")
    {
      if(curnode->children[1]->name == "identifier")
      {
        string idf = curnode->children[1]->children[1]->name;
        curnode->csestring = idf + to_string(currentSSA[idf]);
      }
      else if(curnode->children[1]->name == "integerLit")
        curnode->csestring = curnode->children[1]->children[1]->name;
      else // Pexpr -> (expr)
        curnode->csestring = string("(") + curnode->children[2]->csestring + string(")");
    }
    else if(nodeName == "expr")
    {
      if(curnode->num_child == 1 && curnode->children[1]->name == "Pexpr")
        curnode->csestring = curnode->children[1]->csestring;
      else if(curnode->num_child == 1)
      {
        curnode->csestring = (curnode->children[1]->children[1]->csestring) + (curnode->children[1]->name) + (curnode->children[1]->children[2]->csestring);
        CSEOccurrences[curnode->csestring].push_back(make_pair(make_pair(currentSection, curnode->lineno), curnode));
      }
      else if(curnode->num_child == 2)
      {
        curnode->csestring = (curnode->children[1]->name) + (curnode->children[2]->csestring);
        CSEOccurrences[curnode->csestring].push_back(make_pair(make_pair(currentSection, curnode->lineno), curnode));
      }
    }
    else if(nodeName == "assign_stmt")
    {
      string idf = curnode->children[1]->children[1]->children[1]->name;
      currentSSA[idf] = nextSSA[idf];
      nextSSA[idf] = nextSSA[idf]+1;
    }
    else if(nodeName == "scan_stmt")
    {
      string idf = curnode->children[6]->children[1]->name;
      currentSSA[idf] = nextSSA[idf];
      nextSSA[idf] = nextSSA[idf]+1;
    }
  }
}

void getNodeParents(node* curnode, node* parentnode)
{
  curnode->parent = parentnode;
  for(int i=1; i<=curnode->num_child; i++)
    getNodeParents(curnode->children[i], curnode);

  if(curnode->name == "if_stmt")
    if_stmtNode = curnode;
  else if((curnode->name == "local_decls") && (local_declsNode != NULL))
    local_declsNode = curnode;
}