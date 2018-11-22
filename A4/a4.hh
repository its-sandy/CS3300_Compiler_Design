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
#line 162 "a4.y" /* yacc.c:1909  */
struct node *nnode; char *id;

#line 123 "a4.hh" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_A4_HH_INCLUDED  */
