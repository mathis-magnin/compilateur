# Analyseur lexical du compilateur L en FLEX

%{
#include "arbre_abstrait.h"
#include "symboles.h"
%}
%option yylineno
%option nounput
%option noinput


"entier"              {return TYPE_ENTIER;}
"booleen"             {return TYPE_BOOLEEN;}

"="                   {return AFFECTATION;}

"+"                   {return PLUS;}
"-"                   {return MOINS;}
"*"                   {return FOIS;}
"/"                   {return DIVISION;}
"%"                   {return MODULO;}

"=="                  {return EGALITE;}
"!="                  {return DIFFERENCE;}
"<"                   {return INFERIEUR_STRICT;}
">"                   {return SUPERIEUR_STRICT;}
"<="                  {return INFERIEUR_LARGE;}
">="                  {return SUPERIEUR_LARGE;}

"et"                  {return ET;}
"ou"                  {return OU;}
"non"                 {return NON;}

"si"                  {return SI;}
"sinon"               {return SINON;}
"tantque"             {return TANT_QUE;}
"retourner"           {return RETOURNER;}

"ecrire"              {return ECRIRE;}
"lire"                {return LIRE;}

","                   {return VIRGULE;}
";"                   {return POINT_VIRGULE;}
"("                   {return PARENTHESE_OUVRANTE;}
")"                   {return PARENTHESE_FERMANTE;}
"{"                   {return ACCOLADE_OUVRANTE;}
"}"                   {return ACCOLADE_FERMANTE;}

([1-9][0-9]*|0)       {yylval.entier=atoi(yytext); return ENTIER;}
"Vrai"|"Faux"         {yyval.booleen=!strcmp(yytext, "Vrai"); return BOOLEEN;}
[a-zA-Z][a-zA-Z0-9]*  {return IDENTIFIANT;}
[ \t\r\n]             {}
"#".*                 {}

<<EOF>>               {return FIN;}
.                     {fprintf(stderr, "Ligne %d : caractère invalide : %s\n", yylineno, yytext); exit(-1);}


%%
int yywrap(){
  return 1;
}


# ****************************************************************************
# Fonction auxiliaire qui donne le nom des différents tokens
# ****************************************************************************

int token_fermes[] = 
{
  TYPE_ENTIER, TYPE_BOOLEEN, 
  AFFECTATION, 
  PLUS, MOINS, FOIS, DIVISION, MODULO, 
  EGALITE, DIFFERENCE, INFERIEUR_STRICT, SUPERIEUR_STRICT, INFERIEUR_LARGE, SUPERIEUR_LARGE, 
  ET, OU, NON, 
  SI, SINON, TANT_QUE, RETOURNER, 
  ECRIRE, LIRE, 
  VIRGULE, POINT_VIRGULE, PARENTHESE_OUVRANTE, PARENTHESE_FERMANTE, ACCOLADE_OUVRANTE, ACCOLADE_FERMANTE
};

char *str_token[] = 
{
  "entier", "booleen", 
  "=", 
  "+", "-", "*", "/", "%", 
  "==", "!=", "<", ">", "<=", ">=", 
  "et", "ou", "non", 
  "si", "sinon", "tantque", "retourner", 
  "ecrire", "lire", 
  ",", ";", "(", ")", "{", "}"
};


int nbMotsClefs = 6;

void nom_token(int token, char *nom, char *valeur)
{   
  for (int i = 0; i < nbMotsClefs; i++)
  {
  	if (token == token_fermes[i])
    {
  	  strcpy(nom, "symbole");
  	  strcpy(valeur, str_token[i]);
  	  return;
  	}
  }
  
  if (token == ENTIER)
  {
    strcpy(nom, "entier");
    strcpy(valeur, yytext);
  }
  else if (token == IDENTIFIANT)
  {
    strcpy(nom, "identifiant");  
    strcpy(valeur, yytext);      
  }
  else if (token == BOOLEEN)
  {
    strcpy(nom, "booleen");  
    strcpy(valeur, yytext);  
  }
}


# Fonction auxiliaire appelée par le compilateur en mode -l pour tester l'analyse
# lexicale. Le fichier source doit être indiqué dans la variable globale yyin.
# Cette fonction imprime le résultat de l'analyse lexicale sur la sortie standard.
void afficher_analyse_lexicale() 
{
  int uniteCourante;
  char nom[100];
  char valeur[100]; 
  uniteCourante = yylex();  
  while (uniteCourante != FIN) 
  {
    nom_token(uniteCourante, nom, valeur);
    printf("%s\t%s\t%s\n", yytext, nom, valeur);
    uniteCourante = yylex(); 
  } 
}