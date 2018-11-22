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
    ASS_OP = 264,
    IDENTIFIER_TOK = 265,
    INT_LITERAL = 266,
    FLOAT_LITERAL = 267,
    PLUSMIN = 268,
    STAR = 269,
    pexp = 270,
    onlyif = 271,
    ELSE_TOK = 272,
    LOG_OR = 273,
    LOG_AND = 274,
    REL_OP2 = 275,
    REL_OP1 = 276,
    binplusmin = 277,
    binstar = 278,
    BINARY_OP = 279,
    UNARY_OP = 280,
    unplusmin = 281,
    unstar = 282,
    array = 283,
    function = 284
  };
#endif
/* Tokens.  */
#define DATA_TYPE 258
#define IF_TOK 259
#define WHILE_TOK 260
#define BREAK_TOK 261
#define CONTINUE_TOK 262
#define RETURN_TOK 263
#define ASS_OP 264
#define IDENTIFIER_TOK 265
#define INT_LITERAL 266
#define FLOAT_LITERAL 267
#define PLUSMIN 268
#define STAR 269
#define pexp 270
#define onlyif 271
#define ELSE_TOK 272
#define LOG_OR 273
#define LOG_AND 274
#define REL_OP2 275
#define REL_OP1 276
#define binplusmin 277
#define binstar 278
#define BINARY_OP 279
#define UNARY_OP 280
#define unplusmin 281
#define unstar 282
#define array 283
#define function 284

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 122 "a2.y" /* yacc.c:1909  */
struct node *nnode; char *id;

#line 115 "a2.hh" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_A2_HH_INCLUDED  */
