/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "a4.y" /* yacc.c:339  */

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


#line 227 "a4.cc" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "a4.hh".  */
#ifndef YY_YY_A4_HH_INCLUDED
# define YY_YY_A4_HH_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    DATA_TYPE = 258,
    IF_TOK = 259,
    WHILE_TOK = 260,
    BREAK_TOK = 261,
    CONTINUE_TOK = 262,
    RETURN_TOK = 263,
    PRINTF_TOK = 264,
    SCANF_TOK = 265,
    ASS_OP = 266,
    IDENTIFIER_TOK = 267,
    INT_LITERAL = 268,
    FLOAT_LITERAL = 269,
    PLUSMIN = 270,
    STAR = 271,
    PRINT_FORMAT_SPECIFIER = 272,
    SCAN_FORMAT_SPECIFIER = 273,
    pexp = 274,
    onlyif = 275,
    ELSE_TOK = 276,
    LOG_OR = 277,
    LOG_AND = 278,
    REL_OP2 = 279,
    REL_OP1 = 280,
    binplusmin = 281,
    binstar = 282,
    BINARY_OP = 283,
    UNARY_OP = 284,
    unplusmin = 285,
    unstar = 286,
    array = 287,
    function = 288
  };
#endif
/* Tokens.  */
#define DATA_TYPE 258
#define IF_TOK 259
#define WHILE_TOK 260
#define BREAK_TOK 261
#define CONTINUE_TOK 262
#define RETURN_TOK 263
#define PRINTF_TOK 264
#define SCANF_TOK 265
#define ASS_OP 266
#define IDENTIFIER_TOK 267
#define INT_LITERAL 268
#define FLOAT_LITERAL 269
#define PLUSMIN 270
#define STAR 271
#define PRINT_FORMAT_SPECIFIER 272
#define SCAN_FORMAT_SPECIFIER 273
#define pexp 274
#define onlyif 275
#define ELSE_TOK 276
#define LOG_OR 277
#define LOG_AND 278
#define REL_OP2 279
#define REL_OP1 280
#define binplusmin 281
#define binstar 282
#define BINARY_OP 283
#define UNARY_OP 284
#define unplusmin 285
#define unstar 286
#define array 287
#define function 288

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 162 "a4.y" /* yacc.c:355  */
struct node *nnode; char *id;

#line 336 "a4.cc" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_A4_HH_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 353 "a4.cc" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   167

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  42
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  71
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  147

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   288

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      38,    39,     2,     2,    35,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    34,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    36,     2,    37,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    40,     2,    41,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   179,   179,   182,   183,   186,   187,   190,   191,   192,
     193,   196,   197,   200,   203,   204,   207,   210,   211,   214,
     215,   218,   219,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   233,   236,   239,   242,   245,   246,   249,   250,
     253,   254,   257,   258,   261,   264,   267,   268,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   286,   287,   288,   289,   292,   295,   298,   301,   302,
     305,   306
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DATA_TYPE", "IF_TOK", "WHILE_TOK",
  "BREAK_TOK", "CONTINUE_TOK", "RETURN_TOK", "PRINTF_TOK", "SCANF_TOK",
  "ASS_OP", "IDENTIFIER_TOK", "INT_LITERAL", "FLOAT_LITERAL", "PLUSMIN",
  "STAR", "PRINT_FORMAT_SPECIFIER", "SCAN_FORMAT_SPECIFIER", "pexp",
  "onlyif", "ELSE_TOK", "LOG_OR", "LOG_AND", "REL_OP2", "REL_OP1",
  "binplusmin", "binstar", "BINARY_OP", "UNARY_OP", "unplusmin", "unstar",
  "array", "function", "';'", "','", "'['", "']'", "'('", "')'", "'{'",
  "'}'", "$accept", "program", "decl_list", "decl", "var_decl",
  "type_spec", "func_decl", "params", "epsilon", "param_list", "param",
  "stmt_list", "stmt", "print_stmt", "scan_stmt", "while_stmt",
  "compound_stmt", "local_decls", "local_decl", "if_stmt", "return_stmt",
  "break_stmt", "continue_stmt", "assign_stmt", "expr", "Pexpr",
  "integerLit", "floatLit", "identifier", "arg_list", "args", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,    59,    44,    91,    93,    40,    41,
     123,   125
};
# endif

#define YYPACT_NINF -61

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-61)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      10,     1,    31,    10,   -61,   -61,    25,   -61,   -61,   -61,
     -61,   -61,    79,   -61,    10,    28,    10,   -61,    25,   -61,
      16,    25,    30,   -61,     3,   -61,   -15,   -30,    35,    33,
      10,   -61,    10,    37,   -61,   -61,   -61,   -61,   -61,   -61,
      42,    38,    40,    45,    46,    43,    47,    59,    25,    99,
     -61,   -61,   -61,   -61,   -61,   -61,   -61,   -61,   -61,   -61,
     -61,    -1,   119,   119,   -61,   -61,   -61,    -5,    -5,    -5,
     -61,   119,    49,   122,   -61,   -61,   -22,    67,    80,    32,
     -61,   -61,   119,   119,    60,    61,   -61,   -61,   -61,   -61,
      90,   -61,    -5,    -5,    -5,    -5,    -5,    -5,    -5,   119,
     119,    83,   106,   -61,   119,   108,   112,    20,    20,   -61,
     -61,   -61,   -61,   -61,   -61,   -61,   -61,   114,   -61,   -61,
     117,   104,    25,   124,   118,   -61,   143,   135,   -61,   -61,
     119,   -61,   120,    25,   126,   119,    20,   -61,   127,   123,
     -61,   129,   -61,   -61,   130,   -61,   -61
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    11,     0,     2,     4,     5,     0,     6,    12,     1,
       3,    67,     0,     7,     0,     0,    16,     8,     0,    65,
       0,     0,     0,    15,    14,    18,     0,     0,    19,     0,
       0,     9,     0,     0,    16,    13,    17,    10,    20,    37,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      22,    30,    31,    26,    24,    36,    25,    27,    28,    29,
      23,     0,     0,     0,    44,    45,    66,     0,     0,     0,
      42,     0,     0,    58,    61,    62,    63,     0,     0,     0,
      35,    21,     0,     0,     0,     0,    55,    63,    56,    57,
       0,    43,     0,     0,     0,     0,     0,     0,     0,     0,
      16,     0,     0,    38,     0,     0,     0,     0,     0,    64,
      52,    53,    48,    49,    50,    51,    54,     0,    71,    69,
      70,     0,     0,     0,     0,    46,     0,    40,    34,    60,
       0,    59,     0,     0,     0,     0,     0,    68,     0,     0,
      39,     0,    41,    32,     0,    47,    33
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -61,   -61,   -61,   155,     4,    96,   -61,   -61,   -33,   -61,
     136,   -61,   -43,   -61,   -61,   -61,   138,   -61,   -61,   -61,
     -61,   -61,   -61,   -61,   -60,    27,   150,   -61,    -6,   -61,
     -61
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,     4,     5,     6,     7,    22,    23,    24,
      25,    49,    50,    51,    52,    53,    54,    40,    55,    56,
      57,    58,    59,    60,    72,    73,    74,    75,    76,   120,
     121
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      12,    39,    84,    85,    31,    32,    81,    11,    19,    66,
      82,    90,    26,     1,    99,    28,   100,     8,    17,    13,
      14,    15,   105,   106,    41,    42,    43,    44,    45,    46,
      47,     9,    11,    71,    61,    83,    37,    11,    30,   117,
     119,    19,    79,    61,   124,     1,    41,    42,    43,    44,
      45,    46,    47,    27,    11,    11,    19,    66,    67,    68,
      34,    87,    87,    87,   127,   128,   103,   118,   104,    29,
     137,    33,    69,    34,    38,   141,    62,    70,    63,    64,
      65,    71,    34,    91,   101,    77,    87,    87,    87,    87,
      87,    87,    87,   142,    86,    88,    89,    78,   102,   107,
     108,    61,    61,    41,    42,    43,    44,    45,    46,    47,
      18,    11,    21,    13,    14,    15,   132,    16,   122,   110,
     111,   112,   113,   114,   115,   116,    21,   139,    18,   109,
      61,    11,    19,    66,    67,    68,    48,    92,    93,    34,
      80,   123,   125,   131,    94,    95,    96,    97,    69,   126,
      98,   129,   130,   133,   135,   134,   136,    71,    10,   138,
     140,   143,   144,   145,   146,    20,    36,    35
};

static const yytype_uint8 yycheck[] =
{
       6,    34,    62,    63,    34,    35,    49,    12,    13,    14,
      11,    71,    18,     3,    36,    21,    38,    16,    14,    34,
      35,    36,    82,    83,     4,     5,     6,     7,     8,     9,
      10,     0,    12,    38,    40,    36,    32,    12,    35,    99,
     100,    13,    48,    49,   104,     3,     4,     5,     6,     7,
       8,     9,    10,    37,    12,    12,    13,    14,    15,    16,
      40,    67,    68,    69,   107,   108,    34,   100,    36,    39,
     130,    36,    29,    40,    37,   135,    38,    34,    38,    34,
      34,    38,    40,    34,    17,    38,    92,    93,    94,    95,
      96,    97,    98,   136,    67,    68,    69,    38,    18,    39,
      39,   107,   108,     4,     5,     6,     7,     8,     9,    10,
      14,    12,    16,    34,    35,    36,   122,    38,    35,    92,
      93,    94,    95,    96,    97,    98,    30,   133,    32,    39,
     136,    12,    13,    14,    15,    16,    40,    15,    16,    40,
      41,    35,    34,    39,    22,    23,    24,    25,    29,    37,
      28,    37,    35,    29,    11,    37,    21,    38,     3,    39,
      34,    34,    39,    34,    34,    15,    30,    29
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    43,    44,    45,    46,    47,    48,    16,     0,
      45,    12,    70,    34,    35,    36,    38,    46,    47,    13,
      68,    47,    49,    50,    51,    52,    70,    37,    70,    39,
      35,    34,    35,    36,    40,    58,    52,    46,    37,    50,
      59,     4,     5,     6,     7,     8,     9,    10,    47,    53,
      54,    55,    56,    57,    58,    60,    61,    62,    63,    64,
      65,    70,    38,    38,    34,    34,    14,    15,    16,    29,
      34,    38,    66,    67,    68,    69,    70,    38,    38,    70,
      41,    54,    11,    36,    66,    66,    67,    70,    67,    67,
      66,    34,    15,    16,    22,    23,    24,    25,    28,    36,
      38,    17,    18,    34,    36,    66,    66,    39,    39,    39,
      67,    67,    67,    67,    67,    67,    67,    66,    50,    66,
      71,    72,    35,    35,    66,    34,    37,    54,    54,    37,
      35,    39,    70,    29,    37,    11,    21,    66,    39,    70,
      34,    66,    54,    34,    39,    34,    34
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    42,    43,    44,    44,    45,    45,    46,    46,    46,
      46,    47,    47,    48,    49,    49,    50,    51,    51,    52,
      52,    53,    53,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    55,    56,    57,    58,    59,    59,    60,    60,
      61,    61,    62,    62,    63,    64,    65,    65,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    67,    67,    67,    67,    68,    69,    70,    71,    71,
      72,    72
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     3,     4,     6,
       7,     1,     2,     6,     1,     1,     0,     3,     1,     2,
       4,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     7,     8,     5,     4,     2,     1,     3,     6,
       5,     7,     2,     3,     2,     2,     4,     7,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     2,     1,     4,
       4,     1,     1,     1,     3,     1,     1,     1,     3,     1,
       1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 179 "a4.y" /* yacc.c:1646  */
    {makeTree; rootnode = yyval.nnode;}
#line 1537 "a4.cc" /* yacc.c:1646  */
    break;

  case 3:
#line 182 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1543 "a4.cc" /* yacc.c:1646  */
    break;

  case 4:
#line 183 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1549 "a4.cc" /* yacc.c:1646  */
    break;

  case 5:
#line 186 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1555 "a4.cc" /* yacc.c:1646  */
    break;

  case 6:
#line 187 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1561 "a4.cc" /* yacc.c:1646  */
    break;

  case 7:
#line 190 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1567 "a4.cc" /* yacc.c:1646  */
    break;

  case 8:
#line 191 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1573 "a4.cc" /* yacc.c:1646  */
    break;

  case 9:
#line 192 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1579 "a4.cc" /* yacc.c:1646  */
    break;

  case 10:
#line 193 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1585 "a4.cc" /* yacc.c:1646  */
    break;

  case 11:
#line 196 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1591 "a4.cc" /* yacc.c:1646  */
    break;

  case 12:
#line 197 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1597 "a4.cc" /* yacc.c:1646  */
    break;

  case 13:
#line 200 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1603 "a4.cc" /* yacc.c:1646  */
    break;

  case 14:
#line 203 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1609 "a4.cc" /* yacc.c:1646  */
    break;

  case 15:
#line 204 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1615 "a4.cc" /* yacc.c:1646  */
    break;

  case 16:
#line 207 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1621 "a4.cc" /* yacc.c:1646  */
    break;

  case 17:
#line 210 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1627 "a4.cc" /* yacc.c:1646  */
    break;

  case 18:
#line 211 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1633 "a4.cc" /* yacc.c:1646  */
    break;

  case 19:
#line 214 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1639 "a4.cc" /* yacc.c:1646  */
    break;

  case 20:
#line 215 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1645 "a4.cc" /* yacc.c:1646  */
    break;

  case 21:
#line 218 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1651 "a4.cc" /* yacc.c:1646  */
    break;

  case 22:
#line 219 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1657 "a4.cc" /* yacc.c:1646  */
    break;

  case 23:
#line 222 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1663 "a4.cc" /* yacc.c:1646  */
    break;

  case 24:
#line 223 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1669 "a4.cc" /* yacc.c:1646  */
    break;

  case 25:
#line 224 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1675 "a4.cc" /* yacc.c:1646  */
    break;

  case 26:
#line 225 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1681 "a4.cc" /* yacc.c:1646  */
    break;

  case 27:
#line 226 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1687 "a4.cc" /* yacc.c:1646  */
    break;

  case 28:
#line 227 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1693 "a4.cc" /* yacc.c:1646  */
    break;

  case 29:
#line 228 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1699 "a4.cc" /* yacc.c:1646  */
    break;

  case 30:
#line 229 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1705 "a4.cc" /* yacc.c:1646  */
    break;

  case 31:
#line 230 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1711 "a4.cc" /* yacc.c:1646  */
    break;

  case 32:
#line 233 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1717 "a4.cc" /* yacc.c:1646  */
    break;

  case 33:
#line 236 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1723 "a4.cc" /* yacc.c:1646  */
    break;

  case 34:
#line 239 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1729 "a4.cc" /* yacc.c:1646  */
    break;

  case 35:
#line 242 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1735 "a4.cc" /* yacc.c:1646  */
    break;

  case 36:
#line 245 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1741 "a4.cc" /* yacc.c:1646  */
    break;

  case 37:
#line 246 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1747 "a4.cc" /* yacc.c:1646  */
    break;

  case 38:
#line 249 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1753 "a4.cc" /* yacc.c:1646  */
    break;

  case 39:
#line 250 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1759 "a4.cc" /* yacc.c:1646  */
    break;

  case 40:
#line 253 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1765 "a4.cc" /* yacc.c:1646  */
    break;

  case 41:
#line 254 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1771 "a4.cc" /* yacc.c:1646  */
    break;

  case 42:
#line 257 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1777 "a4.cc" /* yacc.c:1646  */
    break;

  case 43:
#line 258 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1783 "a4.cc" /* yacc.c:1646  */
    break;

  case 44:
#line 261 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1789 "a4.cc" /* yacc.c:1646  */
    break;

  case 45:
#line 264 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1795 "a4.cc" /* yacc.c:1646  */
    break;

  case 46:
#line 267 "a4.y" /* yacc.c:1646  */
    {assignStmtTree;}
#line 1801 "a4.cc" /* yacc.c:1646  */
    break;

  case 47:
#line 268 "a4.y" /* yacc.c:1646  */
    {assignArrayStmtTree;}
#line 1807 "a4.cc" /* yacc.c:1646  */
    break;

  case 48:
#line 271 "a4.y" /* yacc.c:1646  */
    {makeBinOpTree;}
#line 1813 "a4.cc" /* yacc.c:1646  */
    break;

  case 49:
#line 272 "a4.y" /* yacc.c:1646  */
    {makeBinOpTree;}
#line 1819 "a4.cc" /* yacc.c:1646  */
    break;

  case 50:
#line 273 "a4.y" /* yacc.c:1646  */
    {makeBinOpTree;}
#line 1825 "a4.cc" /* yacc.c:1646  */
    break;

  case 51:
#line 274 "a4.y" /* yacc.c:1646  */
    {makeBinOpTree;}
#line 1831 "a4.cc" /* yacc.c:1646  */
    break;

  case 52:
#line 275 "a4.y" /* yacc.c:1646  */
    {makeBinOpTree;}
#line 1837 "a4.cc" /* yacc.c:1646  */
    break;

  case 53:
#line 276 "a4.y" /* yacc.c:1646  */
    {makeBinOpTree;}
#line 1843 "a4.cc" /* yacc.c:1646  */
    break;

  case 54:
#line 277 "a4.y" /* yacc.c:1646  */
    {makeBinOpTree;}
#line 1849 "a4.cc" /* yacc.c:1646  */
    break;

  case 55:
#line 278 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1855 "a4.cc" /* yacc.c:1646  */
    break;

  case 56:
#line 279 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1861 "a4.cc" /* yacc.c:1646  */
    break;

  case 57:
#line 280 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1867 "a4.cc" /* yacc.c:1646  */
    break;

  case 58:
#line 281 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1873 "a4.cc" /* yacc.c:1646  */
    break;

  case 59:
#line 282 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1879 "a4.cc" /* yacc.c:1646  */
    break;

  case 60:
#line 283 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1885 "a4.cc" /* yacc.c:1646  */
    break;

  case 61:
#line 286 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1891 "a4.cc" /* yacc.c:1646  */
    break;

  case 62:
#line 287 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1897 "a4.cc" /* yacc.c:1646  */
    break;

  case 63:
#line 288 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1903 "a4.cc" /* yacc.c:1646  */
    break;

  case 64:
#line 289 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1909 "a4.cc" /* yacc.c:1646  */
    break;

  case 65:
#line 292 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1915 "a4.cc" /* yacc.c:1646  */
    break;

  case 66:
#line 295 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1921 "a4.cc" /* yacc.c:1646  */
    break;

  case 67:
#line 298 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1927 "a4.cc" /* yacc.c:1646  */
    break;

  case 68:
#line 301 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1933 "a4.cc" /* yacc.c:1646  */
    break;

  case 69:
#line 302 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1939 "a4.cc" /* yacc.c:1646  */
    break;

  case 70:
#line 305 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1945 "a4.cc" /* yacc.c:1646  */
    break;

  case 71:
#line 306 "a4.y" /* yacc.c:1646  */
    {makeTree;}
#line 1951 "a4.cc" /* yacc.c:1646  */
    break;


#line 1955 "a4.cc" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 310 "a4.y" /* yacc.c:1906  */


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
