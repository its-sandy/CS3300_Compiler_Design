/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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

#ifndef YY_YY_A2_HH_INCLUDED
# define YY_YY_A2_HH_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
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
#line 106 "a2.y" /* yacc.c:1909  */
struct node *nnode; char *id;

#line 119 "a2.hh" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_A2_HH_INCLUDED  */
