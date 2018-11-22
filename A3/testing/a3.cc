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
#line 1 "a3.y" /* yacc.c:339  */

  // Example from http://epaperpress.com/lexandyacc/pry2.html
  #include <bits/stdc++.h>
  using namespace std;

    struct node
    {
      string name;
      int num_child;
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
    void dfstranslate(node *);
    void yyerror(string);
    void paramDFS(node *);

    node* rootnode;
    set<int> nonterminalset;
    extern int yydebug;

    map<string,int> functionSymbolTable;
    map<string,int> argsSize;
    int labelInd;
    int stackLoc,stackLoc2;
    int curArgsSize;
    string returnLabel;
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


#line 179 "a3.cc" /* yacc.c:339  */

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
   by #include "a3.hh".  */
#ifndef YY_YY_A3_HH_INCLUDED
# define YY_YY_A3_HH_INCLUDED
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
    ASS_OP = 265,
    IDENTIFIER_TOK = 266,
    INT_LITERAL = 267,
    FLOAT_LITERAL = 268,
    PLUSMIN = 269,
    STAR = 270,
    FORMAT_SPECIFIER = 271,
    pexp = 272,
    onlyif = 273,
    ELSE_TOK = 274,
    LOG_OR = 275,
    LOG_AND = 276,
    REL_OP2 = 277,
    REL_OP1 = 278,
    binplusmin = 279,
    binstar = 280,
    BINARY_OP = 281,
    UNARY_OP = 282,
    unplusmin = 283,
    unstar = 284,
    array = 285,
    function = 286
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
#define ASS_OP 265
#define IDENTIFIER_TOK 266
#define INT_LITERAL 267
#define FLOAT_LITERAL 268
#define PLUSMIN 269
#define STAR 270
#define FORMAT_SPECIFIER 271
#define pexp 272
#define onlyif 273
#define ELSE_TOK 274
#define LOG_OR 275
#define LOG_AND 276
#define REL_OP2 277
#define REL_OP1 278
#define binplusmin 279
#define binstar 280
#define BINARY_OP 281
#define UNARY_OP 282
#define unplusmin 283
#define unstar 284
#define array 285
#define function 286

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 114 "a3.y" /* yacc.c:355  */
struct node *nnode; char *id;

#line 284 "a3.cc" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_A3_HH_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 301 "a3.cc" /* yacc.c:358  */

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
#define YYLAST   163

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  138

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   286

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
      36,    37,     2,     2,    33,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    32,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    34,     2,    35,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    38,     2,    39,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   131,   131,   134,   135,   138,   139,   142,   143,   144,
     145,   148,   149,   152,   155,   156,   159,   162,   163,   166,
     167,   170,   171,   174,   175,   176,   177,   178,   179,   180,
     181,   184,   187,   190,   193,   194,   197,   198,   201,   202,
     205,   206,   209,   212,   215,   216,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   234,
     235,   236,   237,   240,   243,   246,   249,   250,   253,   254
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DATA_TYPE", "IF_TOK", "WHILE_TOK",
  "BREAK_TOK", "CONTINUE_TOK", "RETURN_TOK", "PRINTF_TOK", "ASS_OP",
  "IDENTIFIER_TOK", "INT_LITERAL", "FLOAT_LITERAL", "PLUSMIN", "STAR",
  "FORMAT_SPECIFIER", "pexp", "onlyif", "ELSE_TOK", "LOG_OR", "LOG_AND",
  "REL_OP2", "REL_OP1", "binplusmin", "binstar", "BINARY_OP", "UNARY_OP",
  "unplusmin", "unstar", "array", "function", "';'", "','", "'['", "']'",
  "'('", "')'", "'{'", "'}'", "$accept", "program", "decl_list", "decl",
  "var_decl", "type_spec", "func_decl", "params", "epsilon", "param_list",
  "param", "stmt_list", "stmt", "print_stmt", "while_stmt",
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
     285,   286,    59,    44,    91,    93,    40,    41,   123,   125
};
# endif

#define YYPACT_NINF -52

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-52)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -2,    -9,    33,    -2,   -52,   -52,    15,   -52,   -52,   -52,
     -52,   -52,   106,   -52,    -2,    25,    -2,   -52,    15,   -52,
      12,    15,     2,   -52,    20,   -52,   -29,    11,    14,    17,
      -2,   -52,    -2,    21,   -52,   -52,   -52,   -52,   -52,   -52,
      16,    22,    36,    30,    44,   114,    41,    15,    62,   -52,
     -52,   -52,   -52,   -52,   -52,   -52,   -52,   -52,   -52,    -3,
     120,   120,   -52,   -52,   -52,    39,    39,    39,   -52,   120,
      47,   137,   -52,   -52,   -23,    64,     4,   -52,   -52,   120,
     120,    45,    57,   -52,   -52,   -52,   -52,    58,   -52,    39,
      39,    39,    39,    39,    39,    39,   120,   120,    24,   -52,
     120,    49,    61,    98,    98,   -52,   -52,   -52,   -52,   -52,
     -52,   -52,   -52,    73,   -52,   -52,    66,    74,    15,    75,
     -52,   103,    95,   -52,   -52,   120,   -52,    85,    91,   120,
      98,   -52,   105,   -52,   111,   -52,   -52,   -52
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    11,     0,     2,     4,     5,     0,     6,    12,     1,
       3,    65,     0,     7,     0,     0,    16,     8,     0,    63,
       0,     0,     0,    15,    14,    18,     0,     0,    19,     0,
       0,     9,     0,     0,    16,    13,    17,    10,    20,    35,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    22,
      30,    26,    24,    34,    25,    27,    28,    29,    23,     0,
       0,     0,    42,    43,    64,     0,     0,     0,    40,     0,
       0,    56,    59,    60,    61,     0,     0,    33,    21,     0,
       0,     0,     0,    53,    61,    54,    55,     0,    41,     0,
       0,     0,     0,     0,     0,     0,     0,    16,     0,    36,
       0,     0,     0,     0,     0,    62,    50,    51,    46,    47,
      48,    49,    52,     0,    69,    67,    68,     0,     0,     0,
      44,     0,    38,    32,    58,     0,    57,     0,     0,     0,
       0,    66,     0,    37,     0,    39,    31,    45
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -52,   -52,   -52,   127,     3,     0,   -52,   -52,   -32,   -52,
     115,   -52,   -40,   -52,   -52,   119,   -52,   -52,   -52,   -52,
     -52,   -52,   -52,   -51,    26,   129,   -52,    -6,   -52,   -52
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,     4,     5,     6,     7,    22,    23,    24,
      25,    48,    49,    50,    51,    52,    40,    53,    54,    55,
      56,    57,    58,    70,    71,    72,    73,    74,   116,   117
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      12,     1,    39,    13,    14,    15,     8,    79,    78,    81,
      82,    96,    26,    97,    18,    28,    21,    17,    87,     1,
      41,    42,    43,    44,    45,    46,    11,    11,   101,   102,
      21,    80,    18,     9,    59,    37,    99,    19,   100,    29,
      47,    76,    59,    31,    32,   113,   115,    27,    33,   119,
      11,    19,    64,    30,    34,    34,    38,   118,    60,    84,
      84,    84,    62,   122,   123,   114,    41,    42,    43,    44,
      45,    46,    61,    11,   131,    69,    63,    75,   134,    88,
      98,   120,   103,    84,    84,    84,    84,    84,    84,    84,
     135,    83,    85,    86,   104,   105,   121,    59,    59,   125,
      34,    77,    41,    42,    43,    44,    45,    46,   124,    11,
     128,   126,   127,   129,   130,   106,   107,   108,   109,   110,
     111,   112,   132,   133,    59,    11,    19,    64,    65,    66,
      10,    11,    19,    64,    65,    66,    34,   136,    13,    14,
      15,    67,    16,   137,    20,    36,    68,    67,    35,     0,
      69,    89,    90,     0,     0,     0,    69,    91,    92,    93,
      94,     0,     0,    95
};

static const yytype_int16 yycheck[] =
{
       6,     3,    34,    32,    33,    34,    15,    10,    48,    60,
      61,    34,    18,    36,    14,    21,    16,    14,    69,     3,
       4,     5,     6,     7,     8,     9,    11,    11,    79,    80,
      30,    34,    32,     0,    40,    32,    32,    12,    34,    37,
      40,    47,    48,    32,    33,    96,    97,    35,    34,   100,
      11,    12,    13,    33,    38,    38,    35,    33,    36,    65,
      66,    67,    32,   103,   104,    97,     4,     5,     6,     7,
       8,     9,    36,    11,   125,    36,    32,    36,   129,    32,
      16,    32,    37,    89,    90,    91,    92,    93,    94,    95,
     130,    65,    66,    67,    37,    37,    35,   103,   104,    33,
      38,    39,     4,     5,     6,     7,     8,     9,    35,    11,
      35,    37,   118,    10,    19,    89,    90,    91,    92,    93,
      94,    95,    37,    32,   130,    11,    12,    13,    14,    15,
       3,    11,    12,    13,    14,    15,    38,    32,    32,    33,
      34,    27,    36,    32,    15,    30,    32,    27,    29,    -1,
      36,    14,    15,    -1,    -1,    -1,    36,    20,    21,    22,
      23,    -1,    -1,    26
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    41,    42,    43,    44,    45,    46,    15,     0,
      43,    11,    67,    32,    33,    34,    36,    44,    45,    12,
      65,    45,    47,    48,    49,    50,    67,    35,    67,    37,
      33,    32,    33,    34,    38,    55,    50,    44,    35,    48,
      56,     4,     5,     6,     7,     8,     9,    45,    51,    52,
      53,    54,    55,    57,    58,    59,    60,    61,    62,    67,
      36,    36,    32,    32,    13,    14,    15,    27,    32,    36,
      63,    64,    65,    66,    67,    36,    67,    39,    52,    10,
      34,    63,    63,    64,    67,    64,    64,    63,    32,    14,
      15,    20,    21,    22,    23,    26,    34,    36,    16,    32,
      34,    63,    63,    37,    37,    37,    64,    64,    64,    64,
      64,    64,    64,    63,    48,    63,    68,    69,    33,    63,
      32,    35,    52,    52,    35,    33,    37,    67,    35,    10,
      19,    63,    37,    32,    63,    52,    32,    32
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    40,    41,    42,    42,    43,    43,    44,    44,    44,
      44,    45,    45,    46,    47,    47,    48,    49,    49,    50,
      50,    51,    51,    52,    52,    52,    52,    52,    52,    52,
      52,    53,    54,    55,    56,    56,    57,    57,    58,    58,
      59,    59,    60,    61,    62,    62,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    64,
      64,    64,    64,    65,    66,    67,    68,    68,    69,    69
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     3,     4,     6,
       7,     1,     2,     6,     1,     1,     0,     3,     1,     2,
       4,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     7,     5,     4,     2,     1,     3,     6,     5,     7,
       2,     3,     2,     2,     4,     7,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     2,     1,     4,     4,     1,
       1,     1,     3,     1,     1,     1,     3,     1,     1,     1
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
#line 131 "a3.y" /* yacc.c:1646  */
    {makeTree; rootnode = yyval.nnode;}
#line 1475 "a3.cc" /* yacc.c:1646  */
    break;

  case 3:
#line 134 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1481 "a3.cc" /* yacc.c:1646  */
    break;

  case 4:
#line 135 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1487 "a3.cc" /* yacc.c:1646  */
    break;

  case 5:
#line 138 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1493 "a3.cc" /* yacc.c:1646  */
    break;

  case 6:
#line 139 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1499 "a3.cc" /* yacc.c:1646  */
    break;

  case 7:
#line 142 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1505 "a3.cc" /* yacc.c:1646  */
    break;

  case 8:
#line 143 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1511 "a3.cc" /* yacc.c:1646  */
    break;

  case 9:
#line 144 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1517 "a3.cc" /* yacc.c:1646  */
    break;

  case 10:
#line 145 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1523 "a3.cc" /* yacc.c:1646  */
    break;

  case 11:
#line 148 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1529 "a3.cc" /* yacc.c:1646  */
    break;

  case 12:
#line 149 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1535 "a3.cc" /* yacc.c:1646  */
    break;

  case 13:
#line 152 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1541 "a3.cc" /* yacc.c:1646  */
    break;

  case 14:
#line 155 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1547 "a3.cc" /* yacc.c:1646  */
    break;

  case 15:
#line 156 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1553 "a3.cc" /* yacc.c:1646  */
    break;

  case 16:
#line 159 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1559 "a3.cc" /* yacc.c:1646  */
    break;

  case 17:
#line 162 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1565 "a3.cc" /* yacc.c:1646  */
    break;

  case 18:
#line 163 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1571 "a3.cc" /* yacc.c:1646  */
    break;

  case 19:
#line 166 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1577 "a3.cc" /* yacc.c:1646  */
    break;

  case 20:
#line 167 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1583 "a3.cc" /* yacc.c:1646  */
    break;

  case 21:
#line 170 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1589 "a3.cc" /* yacc.c:1646  */
    break;

  case 22:
#line 171 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1595 "a3.cc" /* yacc.c:1646  */
    break;

  case 23:
#line 174 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1601 "a3.cc" /* yacc.c:1646  */
    break;

  case 24:
#line 175 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1607 "a3.cc" /* yacc.c:1646  */
    break;

  case 25:
#line 176 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1613 "a3.cc" /* yacc.c:1646  */
    break;

  case 26:
#line 177 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1619 "a3.cc" /* yacc.c:1646  */
    break;

  case 27:
#line 178 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1625 "a3.cc" /* yacc.c:1646  */
    break;

  case 28:
#line 179 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1631 "a3.cc" /* yacc.c:1646  */
    break;

  case 29:
#line 180 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1637 "a3.cc" /* yacc.c:1646  */
    break;

  case 30:
#line 181 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1643 "a3.cc" /* yacc.c:1646  */
    break;

  case 31:
#line 184 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1649 "a3.cc" /* yacc.c:1646  */
    break;

  case 32:
#line 187 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1655 "a3.cc" /* yacc.c:1646  */
    break;

  case 33:
#line 190 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1661 "a3.cc" /* yacc.c:1646  */
    break;

  case 34:
#line 193 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1667 "a3.cc" /* yacc.c:1646  */
    break;

  case 35:
#line 194 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1673 "a3.cc" /* yacc.c:1646  */
    break;

  case 36:
#line 197 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1679 "a3.cc" /* yacc.c:1646  */
    break;

  case 37:
#line 198 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1685 "a3.cc" /* yacc.c:1646  */
    break;

  case 38:
#line 201 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1691 "a3.cc" /* yacc.c:1646  */
    break;

  case 39:
#line 202 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1697 "a3.cc" /* yacc.c:1646  */
    break;

  case 40:
#line 205 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1703 "a3.cc" /* yacc.c:1646  */
    break;

  case 41:
#line 206 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1709 "a3.cc" /* yacc.c:1646  */
    break;

  case 42:
#line 209 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1715 "a3.cc" /* yacc.c:1646  */
    break;

  case 43:
#line 212 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1721 "a3.cc" /* yacc.c:1646  */
    break;

  case 44:
#line 215 "a3.y" /* yacc.c:1646  */
    {assignStmtTree;}
#line 1727 "a3.cc" /* yacc.c:1646  */
    break;

  case 45:
#line 216 "a3.y" /* yacc.c:1646  */
    {assignArrayStmtTree;}
#line 1733 "a3.cc" /* yacc.c:1646  */
    break;

  case 46:
#line 219 "a3.y" /* yacc.c:1646  */
    {makeBinOpTree;}
#line 1739 "a3.cc" /* yacc.c:1646  */
    break;

  case 47:
#line 220 "a3.y" /* yacc.c:1646  */
    {makeBinOpTree;}
#line 1745 "a3.cc" /* yacc.c:1646  */
    break;

  case 48:
#line 221 "a3.y" /* yacc.c:1646  */
    {makeBinOpTree;}
#line 1751 "a3.cc" /* yacc.c:1646  */
    break;

  case 49:
#line 222 "a3.y" /* yacc.c:1646  */
    {makeBinOpTree;}
#line 1757 "a3.cc" /* yacc.c:1646  */
    break;

  case 50:
#line 223 "a3.y" /* yacc.c:1646  */
    {makeBinOpTree;}
#line 1763 "a3.cc" /* yacc.c:1646  */
    break;

  case 51:
#line 224 "a3.y" /* yacc.c:1646  */
    {makeBinOpTree;}
#line 1769 "a3.cc" /* yacc.c:1646  */
    break;

  case 52:
#line 225 "a3.y" /* yacc.c:1646  */
    {makeBinOpTree;}
#line 1775 "a3.cc" /* yacc.c:1646  */
    break;

  case 53:
#line 226 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1781 "a3.cc" /* yacc.c:1646  */
    break;

  case 54:
#line 227 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1787 "a3.cc" /* yacc.c:1646  */
    break;

  case 55:
#line 228 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1793 "a3.cc" /* yacc.c:1646  */
    break;

  case 56:
#line 229 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1799 "a3.cc" /* yacc.c:1646  */
    break;

  case 57:
#line 230 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1805 "a3.cc" /* yacc.c:1646  */
    break;

  case 58:
#line 231 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1811 "a3.cc" /* yacc.c:1646  */
    break;

  case 59:
#line 234 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1817 "a3.cc" /* yacc.c:1646  */
    break;

  case 60:
#line 235 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1823 "a3.cc" /* yacc.c:1646  */
    break;

  case 61:
#line 236 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1829 "a3.cc" /* yacc.c:1646  */
    break;

  case 62:
#line 237 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1835 "a3.cc" /* yacc.c:1646  */
    break;

  case 63:
#line 240 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1841 "a3.cc" /* yacc.c:1646  */
    break;

  case 64:
#line 243 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1847 "a3.cc" /* yacc.c:1646  */
    break;

  case 65:
#line 246 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1853 "a3.cc" /* yacc.c:1646  */
    break;

  case 66:
#line 249 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1859 "a3.cc" /* yacc.c:1646  */
    break;

  case 67:
#line 250 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1865 "a3.cc" /* yacc.c:1646  */
    break;

  case 68:
#line 253 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1871 "a3.cc" /* yacc.c:1646  */
    break;

  case 69:
#line 254 "a3.y" /* yacc.c:1646  */
    {makeTree;}
#line 1877 "a3.cc" /* yacc.c:1646  */
    break;


#line 1881 "a3.cc" /* yacc.c:1646  */
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
#line 258 "a3.y" /* yacc.c:1906  */


void yyerror(string s) {
    fprintf(stdout, "Invalid\n");
}

int main(void) {

  // yydebug = 1;
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
    cout<<"\t.text\n";
  }
  else if(nodeName == "var_decl")
  {
    string varname = ((curnode->children[2])->children[1])->name;
    cout<<"\t.comm\t"<<varname<<",4,4\n";
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
    //cout<<"\tsubq  $16, \%rsp\n";
    cout<<endl;
  }
  else if(nodeName == "local_decl")
  {
    string varname = ((curnode->children[2])->children[1])->name;
    cout<<"\tsubq  $4, \%rsp\n";
    stackLoc-=4;
    functionSymbolTable[varname] = stackLoc;
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
    }
    else if(curnode->children[1]->name == "identifier")
    {

      string idf = curnode->children[1]->children[1]->name;
      if(functionSymbolTable.find(idf) == functionSymbolTable.end())
        cout<<"\tmovl\t"<<idf<<"(\%rip), \%eax\n";
      else
        cout<<"\tmovl\t"<< functionSymbolTable[idf] <<"(\%rbp), \%eax\n";
      
      cout<<"\tpushq\t\%rax\n";
    }
    cout<<endl;
  }
  if(nodeName == "expr")
  {
    if(curnode->num_child == 1 && curnode->children[1]->name != "Pexpr")
    {
      string op = curnode->children[1]->name;

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
      else if(op == "!=" || op == "==" || op == "<=" || op == ">=" || op == ">" || op == "<")
      {
        cout<<"\tcmpl\t\%edx, \%eax\n";
        if(op == "!=")
          cout<<"\tsetne\t\%al\n";
        else if(op == "==")
          cout<<"\tsete\t\%al\n";
        else if(op == ">=")
          cout<<"\tsetge\t\%al\n";
        else if(op == "<=")
          cout<<"\tsetle\t\%al\n";
        else if(op == ">")
          cout<<"\tsetg\t\%al\n";
        else if(op == "<")
          cout<<"\tsetl\t\%al\n";
        cout<<"\tmovzbl\t\%al, \%eax\n";
        cout<<"\tpushq\t\%rax\n";
      }
      else if(op == "&&")
      {
        string label1 = getNextLabel();
        string label2 = getNextLabel();

        cout<<"\tcmpl\t$0, \%eax\n";
        cout<<"\tje\t"<<label1<<endl;
        cout<<"\tcmpl\t$0, \%edx\n";
        cout<<"\tje\t"<<label1<<endl;
        cout<<"\tmovl\t$1, \%eax\n";
        cout<<"\tjmp\t"<<label2<<endl;
        cout<<label1<<":\n";
        cout<<"\tmovl\t$0, \%eax\n";
        cout<<label2<<":\n";
        cout<<"\tpushq\t\%rax\n";
      }
      else if(op == "||")
      {
        string label1 = getNextLabel();
        string label2 = getNextLabel();
        string label3 = getNextLabel();

        cout<<"\tcmpl\t$0, \%eax\n";
        cout<<"\tjne\t"<<label1<<endl;
        cout<<"\tcmpl\t$0, \%edx\n";
        cout<<"\tje\t"<<label2<<endl;
        cout<<label1<<":\n";
        cout<<"\tmovl\t$1, \%eax\n";
        cout<<"\tjmp\t"<<label3<<endl;
        cout<<label2<<":\n";
        cout<<"\tmovl\t$0, \%eax\n";
        cout<<label3<<":\n";
        cout<<"\tpushq\t\%rax\n";
      }

      if(op == "%")
        cout<<"\tpushq\t\%rdx\n";
      else if(op == "+" || op == "-" || op == "*" || op == "/")
        cout<<"\tpushq\t\%rax\n";
      cout<<endl;
    }
    else if(curnode->num_child == 2)
    {
      string op = curnode->children[1]->name;

      if(op == "-")
      {
        cout<<"\tpopq\t\%rax\n";
        cout<<"\tnegl\t\%eax\n";
        cout<<"\tpushq\t\%rax\n";
      }
      else if(op == "!")
      {
        cout<<"\tpopq\t\%rax\n";
        cout<<"\tcmpl\t$0, \%eax\n";
        cout<<"\tsete\t\%al\n";
        cout<<"\tmovzbl\t\%al, \%eax\n";
        cout<<"\tpushq\t\%rax\n";
      }
      cout<<endl;
    }
    else if(curnode->num_child == 4 && curnode->children[2]->name == "(")
    {
      string funname = curnode->children[1]->children[1]->name;
      cout<<"\tcall\t"<<funname<<endl;
      cout<<"\taddq  $"<<argsSize[funname]<<", \%rsp\n";
      cout<<"\tpushq\t\%rax\n";
    }
  }
  else if(nodeName == "assign_stmt")
  {
    cout<<"\tpopq\t\%rax\n";
    string idf = curnode->children[1]->children[1]->children[1]->name;

    if(curnode->children[1]->num_child == 2)
    {
      if(functionSymbolTable.find(idf) == functionSymbolTable.end())
        cout<<"\tmovl\t\%eax, "<<idf<<"(\%rip)\n";
      else
        cout<<"\tmovl\t\%eax, "<< functionSymbolTable[idf] <<"(\%rbp)\n";
    }
    cout<<endl;
  }
  else if(nodeName == "print_stmt")
  {
    string idf = curnode->children[5]->children[1]->name;
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
    string funname = ((curnode->children[2])->children[1])->name;
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
  }
  for(int i=curnode->num_child; i>=1; i--)
    paramDFS(curnode->children[i]);
}
