%{
#include <stdlib.h>
#include <stdio.h>
#include "arbre_abstrait.h"
#include "analyse_lexicale.h"


//n_programme* yyparse();
int yylex();
int yyerror(const char *s);
n_programme* arbre_abstrait;
%}

%union {
    int entier;
    int booleen;
    n_programme* prog;
    n_l_instructions* l_inst;
    n_instruction* inst;
    n_exp* exp;
}


%define parse.error verbose
%define parse.lac full

//Symboles terminaux qui seront fournis par yylex(), ordre non important

%token TYPE_ENTIER
%token TYPE_BOOLEEN

%token AFFECTATION

%token PLUS
%token MOINS
%token FOIS
%token DIVISION
%token MODULO

%token EGALITE
%token DIFFERENCE
%token INFERIEUR_STRICT
%token SUPERIEUR_STRICT
%token INFERIEUR_LARGE
%token SUPERIEUR_LARGE

%token ET
%token OU
%token NON

%token SI
%token SINON
%token TANT_QUE
%token RETOURNER

%token ECRIRE
%token LIRE

%token VIRGULE
%token POINT_VIRGULE
%token PARENTHESE_OUVRANTE
%token PARENTHESE_FERMANTE
%token ACCOLADE_OUVRANTE
%token ACCOLADE_FERMANTE

%token <entier> ENTIER
%token <booleen> BOOLEEN
%token IDENTIFIANT

%token FIN 0


//Symboles non terminaux

%type <prog> prog
%type <l_inst> listeInstructions
%type <inst> instruction
%type <inst> ecrire

%type <exp> expr
%type <exp> entier
%type <exp> somme
%type <exp> produit
%type <exp> facteur
%type <exp> booleen
%type <exp> disjonction
%type <exp> conjonction
%type <exp> negation
%type <exp> atome

%%

prog: listeInstructions {
    arbre_abstrait = creer_n_programme($1);
}

listeInstructions: instruction {
    $$ = creer_n_l_instructions($1, NULL);
} 

listeInstructions: instruction listeInstructions {
    $$ = creer_n_l_instructions($1, $2);
} 

instruction: ecrire {
	$$ = $1;
}

ecrire: ECRIRE PARENTHESE_OUVRANTE expr PARENTHESE_FERMANTE POINT_VIRGULE {
	$$ = creer_n_ecrire($3);
}


// Expressions


expr: entier {
    $$ = $1;
}

expr: booleen {
    $$ = $1;
}

// 1. Expressions entières

entier: somme {
    $$ = $1;
}

somme: somme PLUS produit {
	$$ = creer_n_operation('+', $1, $3);
}

somme: produit {
    $$ = $1;
}

produit: produit FOIS facteur {
	$$ = creer_n_operation('*', $1 , $3);
}

produit: facteur {
    $$ = $1;
}

facteur: ENTIER {
    $$ = creer_n_entier($1);
}

facteur: PARENTHESE_OUVRANTE entier PARENTHESE_FERMANTE {
	$$ = $2;
}

// 2. Expressions booléennes

// a. Comparaisons d'entiers

booleen: entier EGALITE entier {
    $$ = creer_n_operation('↔', $1, $3);
}

booleen: entier DIFFERENCE entier {
    $$ = creer_n_operation('≠', $1, $3);
}

booleen: entier INFERIEUR_LARGE entier {
    $$ = creer_n_operation('≤', $1, $3);
}

booleen: entier INFERIEUR_STRICT entier {
    $$ = creer_n_operation('<', $1, $3);
}

booleen: entier SUPERIEUR_LARGE entier {
    $$ = creer_n_operation('≥', $1, $3);
}

booleen: entier SUPERIEUR_STRICT entier {
    $$ = creer_n_operation('>', $1, $3);
}

// b. Opérations booléennnes

booleen: disjonction {
    $$ = $1;
}

disjonction: disjonction OU conjonction {
    $$ = creer_n_operation('|', $1 , $3);
}

disjonction: conjonction {
    $$ = $1;
}

conjonction: conjonction ET negation {
    $$ = creer_n_operation('&', $1 , $3);
}

conjonction: negation {
    $$ = $1;
}

negation: NON atome {
    $$ = creer_n_operation('!', $2, NULL);
}

negation: atome {
    $$ = $1;
}

atome: BOOLEEN {
    $$ = creer_n_booleen($1);
}

atome: PARENTHESE_OUVRANTE booleen PARENTHESE_FERMANTE {
	$$ = $2;
}


%%

int yyerror(const char *s) {
    printf("yyerror : %s\n",s);
    return 0;
}