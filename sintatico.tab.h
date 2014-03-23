/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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

/* "%code requires" blocks.  */

/* Line 2068 of yacc.c  */
#line 2 "sintatico.y"
 
#include <cstdio>
#include <iostream>
#include "arvore_abstrata.h"
#include "debug.h"



/* Line 2068 of yacc.c  */
#line 47 "sintatico.tab.h"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     CAR = 258,
     INT = 259,
     REAL = 260,
     NULO = 261,
     IDENTIFICADOR = 262,
     PALAVRA_LITERAL = 263,
     INT_CONST = 264,
     REAL_CONST = 265,
     CAR_CONST = 266,
     SE = 267,
     ENQUANTO = 268,
     LEIA = 269,
     ESCREVA = 270,
     RETORNE = 271,
     NOVA_LINHA = 272,
     INC_OP = 273,
     DEC_OP = 274,
     TERMINAR = 275,
     LIMPAR = 276,
     ENTAO = 277,
     EXECUTE = 278,
     SENAO = 279,
     MULT_ATRIBUICAO = 280,
     DIV_ATRIBUICAO = 281,
     MOD_ATRIBUICAO = 282,
     ADICAO_ATRIBUICAO = 283,
     SUBTRACAO_ATRIBUICAO = 284,
     ESQ_ATRIBUICAO = 285,
     DIR_ATRIBUICAO = 286,
     E_ATRIBUICAO = 287,
     XOR_ATRIBUICAO = 288,
     OU_ATRIBUICAO = 289,
     POT_ATRIBUICAO = 290,
     OU_OP = 291,
     E_OP = 292,
     EQ_OP = 293,
     NE_OP = 294,
     LE_OP = 295,
     GE_OP = 296,
     ESQ_OP = 297,
     DIR_OP = 298,
     POT_OP = 299,
     BT_OP = 300,
     LT_OP = 301
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 30 "sintatico.y"

	int ival;
    std::string *sval;
    double dval;
    No* no;
    NBloco *bloco;
    NExpressao *expr;
    NInstrucao *inst;
    NIdentificador *ident;
    NOperacaoUnaria *uni;
    NDeclaracaoVariavel *declVar;
    std::vector<NDeclaracaoVariavel*> *listVar;
    std::vector<NExpressao*> *listExpr;
    std::vector<NInstrucao*> *listInstr;
    NDeclaracaoFuncao *declFunc;
    TipoVariavel::TipoVariavel tipoVar;
    std::vector<int>* vetDim;
    Operador::Operador op;
    NListaExpressoes *nlistExpr;



/* Line 2068 of yacc.c  */
#line 133 "sintatico.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


