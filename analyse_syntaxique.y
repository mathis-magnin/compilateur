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
%type <exp> expr 

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

listeFonctions: listeFonctions fonction {
    $$ = creer_n_l_fonctions($2, $1);
}


fonction: IDENTIFIANT PARENTHESE_OUVRANTE listeParametres PARENTHESE_FERMANTE ACCOLADE_OUVRANTE listeInstructions ACCOLADE_FERMANTE { // type
    $$ = creer_n_fonction($1, $3, $6);
}

fonction: IDENTIFIANT PARENTHESE_OUVRANTE PARENTHESE_FERMANTE ACCOLADE_OUVRANTE listeInstructions ACCOLADE_FERMANTE {
    $$ = creer_n_fonction($1, NULL, $5);
}


listeParametres: parametre {
    $$ = creer_n_l_parametres($1, NULL);
}

listeParametres: parametre VIRGULE listeParametres {
    $$ = creer_n_l_parametres($1, $3);
}


parametre: TYPE_BOOLEEN IDENTIFIANT {
    $$ = creer_n_parametre_booleen($2);
}

parametre: TYPE_ENTIER IDENTIFIANT {
    $$ = creer_n_parametre_entier($2);
}


/* Instructions */

listeInstructions: instruction {
    $$ = creer_n_l_instructions($1, NULL);
} 

listeInstructions: instruction listeInstructions {
    $$ = creer_n_l_instructions($1 ,$2);
} 


instruction: ecrire {
	$$ = $1;
}


ecrire: ECRIRE PARENTHESE_OUVRANTE expr PARENTHESE_FERMANTE POINT_VIRGULE {
	$$ = creer_n_ecrire($3);
}


expr: expr PLUS expr {
	$$ = creer_n_operation('+', $1, $3);
}

expr: expr FOIS expr {
	$$ = creer_n_operation('*', $1 , $3);
}

expr: PARENTHESE_OUVRANTE expr PARENTHESE_FERMANTE {
	$$ = $2 ;
}

expr: ENTIER {
	$$ = creer_n_entier($1);
}


%%

int yyerror(const char *s) {
    printf("yyerror : %s\n",s);
    return 0;
}