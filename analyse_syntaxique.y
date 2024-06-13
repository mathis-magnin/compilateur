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
}


%define parse.error verbose
%define parse.lac full

//Symboles terminaux qui seront fournis par yylex(), ordre non important

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

%token <type> TYPE

%token <entier> ENTIER
%token <booleen> BOOLEEN
%token <identifiant> IDENTIFIANT

%token FIN 0


// Symboles non terminaux
%type <prog> prog

%type <l_fonctions> listeFonctions
%type <fonction> fonction
%type <l_parametres> listeParametres
%type <parametre> parametre

%type <l_inst> listeInstructions
%type <inst> instruction
%type <inst> ecrire
%type <inst> lire


%type <exp> expr

%type <exp> entier
%type <exp> op_prio_0
%type <exp> somme
%type <exp> soustraction
%type <exp> op_prio_1
%type <exp> produit
%type <exp> quotient
%type <exp> reste
%type <exp> op_prio_2
%type <exp> opposition
%type <exp> facteur

%type <exp> booleen
%type <exp> disjonction
%type <exp> conjonction
%type <exp> negation
%type <exp> atome

%%

prog: listeFonctions listeInstructions {
    arbre_abstrait = creer_n_programme($1, $2);
}

prog: listeInstructions {
    arbre_abstrait = creer_n_programme(NULL, $1);
}


/* Fonctions */

listeFonctions: fonction {
    $$ = creer_n_l_fonctions($1, NULL);
}

listeFonctions: fonction listeFonctions {
    $$ = creer_n_l_fonctions($1, $2);
}


fonction: TYPE IDENTIFIANT PARENTHESE_OUVRANTE listeParametres PARENTHESE_FERMANTE ACCOLADE_OUVRANTE listeInstructions ACCOLADE_FERMANTE { // type
    $$ = creer_n_fonction($1, $2, $4, $7);
}

fonction: TYPE IDENTIFIANT PARENTHESE_OUVRANTE PARENTHESE_FERMANTE ACCOLADE_OUVRANTE listeInstructions ACCOLADE_FERMANTE {
    $$ = creer_n_fonction($1, $2, NULL, $6);
}


listeParametres: parametre {
    $$ = creer_n_l_parametres($1, NULL);
}

listeParametres: parametre VIRGULE listeParametres {
    $$ = creer_n_l_parametres($1, $3);
}


parametre: TYPE IDENTIFIANT {
    $$ = creer_n_parametre($1, $2);
}


/* Instructions */

listeInstructions: instruction {
    $$ = creer_n_l_instructions($1, NULL);
} 

listeInstructions: instruction listeInstructions {
    $$ = creer_n_l_instructions($1, $2);
} 


instruction: ecrire {
	$$ = $1;
}

instruction: lire {
    $$ = $1;
}


ecrire: ECRIRE PARENTHESE_OUVRANTE expr PARENTHESE_FERMANTE POINT_VIRGULE {
	$$ = creer_n_ecrire($3);
}

lire: LIRE PARENTHESE_OUVRANTE PARENTHESE_FERMANTE POINT_VIRGULE {
    $$ = creer_n_lire();
}


// Expressions


expr: entier {
    $$ = $1;
}

expr: booleen {
    $$ = $1;
}

// 1. Expressions entières

entier: op_prio_0 {
    $$ = $1;
}

// a. Opérations de priorité 0

op_prio_0: somme {
    $$ = $1;
}

op_prio_0: soustraction {
    $$ = $1;
}

op_prio_0: op_prio_1 {
    $$ = $1;
}

somme: op_prio_0 PLUS op_prio_1 {
	$$ = creer_n_operation(type_op_value[i_plus], $1, $3);
}

soustraction: op_prio_0 MOINS op_prio_1 {
	$$ = creer_n_operation(type_op_value[i_moins], $1, $3);
}

// b. Opérations de priorité 1

op_prio_1: produit {
    $$ = $1;
}

op_prio_1: quotient {
    $$ = $1;
}

op_prio_1: reste {
    $$ = $1;
}

op_prio_1: op_prio_2 {
    $$ = $1;
}

produit: op_prio_1 FOIS op_prio_2 {
	$$ = creer_n_operation(type_op_value[i_fois], $1 , $3);
}

quotient: op_prio_1 DIVISION op_prio_2 {
	$$ = creer_n_operation(type_op_value[i_division], $1 , $3);
}

reste: op_prio_1 MODULO op_prio_2 {
	$$ = creer_n_operation(type_op_value[i_modulo], $1 , $3);
}

// c. Opérations de priorité 2

op_prio_2: opposition {
    $$ = $1;
}

op_prio_2: facteur {
    $$ = $1;
}

opposition: MOINS facteur {
	$$ = creer_n_operation(type_op_value[i_fois], creer_n_entier(-1), $2);
}

// d. Composants de base de l'opération

facteur: ENTIER {
    $$ = creer_n_entier($1);
}

facteur: PARENTHESE_OUVRANTE entier PARENTHESE_FERMANTE {
	$$ = $2;
}

// 2. Expressions booléennes

// a. Comparaisons d'entiers

booleen: entier EGALITE entier {
    $$ = creer_n_operation(type_op_value[i_egalite], $1, $3);
}

booleen: entier DIFFERENCE entier {
    $$ = creer_n_operation(type_op_value[i_difference], $1, $3);
}

booleen: entier INFERIEUR_LARGE entier {
    $$ = creer_n_operation(type_op_value[i_inferieur_large], $1, $3);
}

booleen: entier INFERIEUR_STRICT entier {
    $$ = creer_n_operation(type_op_value[i_inferieur_strict], $1, $3);
}

booleen: entier SUPERIEUR_LARGE entier {
    $$ = creer_n_operation(type_op_value[i_superieur_large], $1, $3);
}

booleen: entier SUPERIEUR_STRICT entier {
    $$ = creer_n_operation(type_op_value[i_superieur_strict], $1, $3);
}

// b. Opérations booléennnes

booleen: disjonction {
    $$ = $1;
}

disjonction: disjonction OU conjonction {
    $$ = creer_n_operation(type_op_value[i_ou], $1 , $3);
}

disjonction: conjonction {
    $$ = $1;
}

conjonction: conjonction ET negation {
    $$ = creer_n_operation(type_op_value[i_et], $1 , $3);
}

conjonction: negation {
    $$ = $1;
}

negation: NON atome {
    $$ = creer_n_operation(type_op_value[i_non], $2, NULL);
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