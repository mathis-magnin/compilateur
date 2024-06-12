/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_SYMBOLES_H_INCLUDED
# define YY_YY_SYMBOLES_H_INCLUDED
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
    FIN = 0,
    AFFECTATION = 258,
    PLUS = 259,
    MOINS = 260,
    FOIS = 261,
    DIVISION = 262,
    MODULO = 263,
    EGALITE = 264,
    DIFFERENCE = 265,
    INFERIEUR_STRICT = 266,
    SUPERIEUR_STRICT = 267,
    INFERIEUR_LARGE = 268,
    SUPERIEUR_LARGE = 269,
    ET = 270,
    OU = 271,
    NON = 272,
    SI = 273,
    SINON = 274,
    TANT_QUE = 275,
    RETOURNER = 276,
    ECRIRE = 277,
    LIRE = 278,
    VIRGULE = 279,
    POINT_VIRGULE = 280,
    PARENTHESE_OUVRANTE = 281,
    PARENTHESE_FERMANTE = 282,
    ACCOLADE_OUVRANTE = 283,
    ACCOLADE_FERMANTE = 284,
    TYPE = 285,
    ENTIER = 286,
    BOOLEEN = 287,
    IDENTIFIANT = 288
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 14 "analyse_syntaxique.y"

    int type;
    int entier;
    int booleen;
    char *identifiant;
    n_programme* prog;
    n_l_instructions* l_inst;
    n_instruction* inst;
    n_exp* exp;
    n_l_fonctions *l_fonctions;
    n_fonction *fonction;
    n_l_parametres *l_parametres;
    n_parametre *parametre;
    n_l_arguments *l_arguments;

#line 108 "symboles.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SYMBOLES_H_INCLUDED  */
