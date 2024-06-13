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
    n_l_arguments *l_arguments;
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
%type <inst> instruction_base
%type <exp> declaration
%type <inst> si


%type <exp> expr

%type <exp> entier
%type <exp> op_ent_prio_0
%type <exp> op_ent_prio_1
%type <exp> op_ent_prio_2
%type <exp> facteur

%type <exp> booleen
%type <exp> disjonction
%type <exp> conjonction
%type <exp> negation
%type <exp> comparaison_entiere
%type <exp> comparaison
%type <exp> atome
/*
%type <exp> indefini
%type <exp> op_ind_prio_0
%type <exp> op_ind_prio_1
%type <exp> op_ind_prio_2
%type <exp> brique_non_typee
%type <exp> variable
%type <exp> appel_fonction
%type <l_arguments> listeArguments
*/

%%

prog: listeFonctions listeInstructions {
    arbre_abstrait = creer_n_programme($1, $2);
}

prog: listeInstructions {
    arbre_abstrait = creer_n_programme(NULL, $1);
}

/*****************************/
/* Déclarations de fonctions */
/*****************************/

listeFonctions: fonction {
    $$ = creer_n_l_fonctions(NULL, $1);
}

listeFonctions: listeFonctions fonction {
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

/****************/
/* Instructions */
/****************/

listeInstructions: instruction {
    $$ = creer_n_l_instructions($1, NULL);
}

listeInstructions: instruction listeInstructions {
    $$ = creer_n_l_instructions($1, $2);
}

instruction: instruction_base POINT_VIRGULE {
    $$ = $1;
}

// 1) a. Instruction de base

instruction_base: ECRIRE PARENTHESE_OUVRANTE expr PARENTHESE_FERMANTE {
	$$ = creer_n_ecrire($3);
}

instruction_base: RETOURNER expr {
    $$ = creer_n_retourner($2);
}

// 1 b. Déclarations et affectations

instruction_base: TYPE IDENTIFIANT declaration {
    $$ = creer_n_declaration($1, $2, $3);
}

instruction_base: IDENTIFIANT AFFECTATION expr {
    $$ = creer_n_affectation($1, $3);
}

declaration: {
    $$ = NULL;
}

declaration: AFFECTATION expr {
    $$ = $2;
}

// 2) Instructions conditionnelles

instruction: TANT_QUE PARENTHESE_OUVRANTE booleen PARENTHESE_FERMANTE ACCOLADE_OUVRANTE listeInstructions ACCOLADE_FERMANTE {
    $$ = creer_n_tant_que($3, $6);
}

instruction: si SINON ACCOLADE_OUVRANTE listeInstructions ACCOLADE_FERMANTE {
    $$ = creer_n_sinon($1, $4);
}

instruction: si {
    $$ = $1;
}

si: SI PARENTHESE_OUVRANTE booleen PARENTHESE_FERMANTE ACCOLADE_OUVRANTE listeInstructions ACCOLADE_FERMANTE {
    $$ = creer_n_si($3, $6);
}

si: si SINON SI PARENTHESE_OUVRANTE booleen PARENTHESE_FERMANTE ACCOLADE_OUVRANTE listeInstructions ACCOLADE_FERMANTE {
    $$ = creer_n_sinon_si($1, $5, $8);
}

/***************/
/* Expressions */
/***************/

expr: entier {
    $$ = $1;
}

expr: booleen {
    $$ = $1;
}
/*
expr: indefini {
    $$ = $1;
}
*/
// 1. Expressions entières

entier: op_ent_prio_0 {
    $$ = $1;
}

// a. Opérations de priorité 0

op_ent_prio_0: op_ent_prio_0 PLUS op_ent_prio_1 {
	$$ = creer_n_operation(type_op_value[i_plus], $1, $3);
}

op_ent_prio_0: op_ent_prio_0 MOINS op_ent_prio_1 {
	$$ = creer_n_operation(type_op_value[i_moins], $1, $3);
}

op_ent_prio_0: op_ent_prio_1 {
    $$ = $1;
}

// b. Opérations de priorité 1

op_ent_prio_1: op_ent_prio_1 FOIS op_ent_prio_2 {
	$$ = creer_n_operation(type_op_value[i_fois], $1 , $3);
}

op_ent_prio_1: op_ent_prio_1 DIVISION op_ent_prio_2 {
	$$ = creer_n_operation(type_op_value[i_division], $1 , $3);
}

op_ent_prio_1: op_ent_prio_1 MODULO op_ent_prio_2 {
	$$ = creer_n_operation(type_op_value[i_modulo], $1 , $3);
}

op_ent_prio_1: op_ent_prio_2 {
    $$ = $1;
}

// c. Opération de priorité 2

op_ent_prio_2: MOINS facteur {
	$$ = creer_n_operation(type_op_value[i_fois], creer_n_entier(-1), $2);
}

op_ent_prio_2: facteur {
    $$ = $1;
}

// d. Composants de base de l'opération

facteur: ENTIER {
    $$ = creer_n_entier($1);
}

facteur: LIRE PARENTHESE_OUVRANTE PARENTHESE_FERMANTE {
    $$ = creer_n_lire();
}

facteur: PARENTHESE_OUVRANTE entier PARENTHESE_FERMANTE {
	$$ = $2;
}

// 2. Expressions booléennes

// a. Opérations booléennnes

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

negation: NON comparaison_entiere {
    $$ = creer_n_operation(type_op_value[i_non], $2, NULL);
}

negation: comparaison_entiere {
    $$ = $1;
}

comparaison_entiere: comparaison {
    $$ = $1;
}

comparaison_entiere: atome {
    $$ = $1;
}

atome: BOOLEEN {
    $$ = creer_n_booleen($1);
}

atome: PARENTHESE_OUVRANTE booleen PARENTHESE_FERMANTE {
	$$ = $2;
}

// b. Comparaisons d'entiers

comparaison: entier EGALITE entier {
    $$ = creer_n_operation(type_op_value[i_egalite], $1, $3);
}

comparaison: entier DIFFERENCE entier {
    $$ = creer_n_operation(type_op_value[i_difference], $1, $3);
}

comparaison: entier INFERIEUR_LARGE entier {
    $$ = creer_n_operation(type_op_value[i_inferieur_large], $1, $3);
}

comparaison: entier INFERIEUR_STRICT entier {
    $$ = creer_n_operation(type_op_value[i_inferieur_strict], $1, $3);
}

comparaison: entier SUPERIEUR_LARGE entier {
    $$ = creer_n_operation(type_op_value[i_superieur_large], $1, $3);
}

comparaison: entier SUPERIEUR_STRICT entier {
    $$ = creer_n_operation(type_op_value[i_superieur_strict], $1, $3);
}

// 3. Expressions indéfinies (contenant une variable ou appel de fonction)
/*
indefini: op_ind_prio_0 {
    $$ = $1;
}

// a. Opérations de priorité 0

op_ind_prio_0: op_ind_prio_0 PLUS op_ind_prio_1 {
	$$ = creer_n_operation(type_op_value[i_plus], $1, $3);
}

op_ind_prio_0: op_ind_prio_0 MOINS op_ind_prio_1 {
	$$ = creer_n_operation(type_op_value[i_moins], $1, $3);
}

op_ind_prio_0: op_ind_prio_0 OU op_ind_prio_1 {
	$$ = creer_n_operation(type_op_value[i_ou], $1, $3);
}

op_ind_prio_0: op_ind_prio_1 {
    $$ = $1;
}

// b. Opérations de priorité 1

op_ind_prio_1: op_ind_prio_1 FOIS op_ind_prio_2 {
	$$ = creer_n_operation(type_op_value[i_fois], $1 , $3);
}

op_ind_prio_1: op_ind_prio_1 DIVISION op_ind_prio_2 {
	$$ = creer_n_operation(type_op_value[i_division], $1 , $3);
}

op_ind_prio_1: op_ind_prio_1 MODULO op_ind_prio_2 {
	$$ = creer_n_operation(type_op_value[i_modulo], $1 , $3);
}

op_ind_prio_1: op_ind_prio_1 ET op_ind_prio_2 {
	$$ = creer_n_operation(type_op_value[i_et], $1 , $3);
}

op_ind_prio_1: op_ind_prio_2 {
    $$ = $1;
}

// c. Opération de priorité 2

op_ind_prio_2: MOINS brique_non_typee {
	$$ = creer_n_operation(type_op_value[i_fois], creer_n_entier(-1), $2);
}

op_ind_prio_2: NON brique_non_typee {
	$$ = creer_n_operation(type_op_value[i_non], $2, NULL);
}

op_ind_prio_2: brique_non_typee {
    $$ = $1;
}

// d. Composants de base de l'opération

brique_non_typee: variable {
    $$ = $1;
}

brique_non_typee: appel_fonction {
    $$ = $1;
}

brique_non_typee: PARENTHESE_OUVRANTE indefini PARENTHESE_FERMANTE {
	$$ = $2;
}

variable: IDENTIFIANT {
    $$ = creer_n_variable($1);
}

appel_fonction: IDENTIFIANT PARENTHESE_OUVRANTE PARENTHESE_FERMANTE {
    $$ = creer_n_appel_fonction($1, NULL);
}

appel_fonction: IDENTIFIANT PARENTHESE_OUVRANTE listeArguments PARENTHESE_FERMANTE {
    $$ = creer_n_appel_fonction($1, $3);
} 

listeArguments: expr {
    $$ = creer_n_l_arguments(NULL, $1);
}

listeArguments: listeArguments VIRGULE expr {
    $$ = creer_n_l_arguments($1, $3);
}
*/
%%

int yyerror(const char *s) {
    printf("yyerror : %s\n",s);
    return 0;
}