/* 
 * Analyseur lexical du compilateur L en FLEX 
 */

%{
#include "arbre_abstrait.h"
#include "symboles.h"
%}
%option yylineno
%option nounput
%option noinput

%%
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

("entier"|"booleen")  {yylval.type=!strcmp(yytext, "entier")?0:1; return TYPE;}

([1-9][0-9]*|0)       {yylval.entier=atoi(yytext); return ENTIER;}
("Vrai"|"Faux")       {yylval.booleen=!strcmp(yytext, "Vrai"); return BOOLEEN;}
[a-zA-Z][a-zA-Z0-9]*  {yylval.identifiant=malloc(sizeof(char)*(strlen(yytext)+1)); strcpy(yylval.identifiant,yytext); return IDENTIFIANT;}
[ \t\r\n]             {}
"#".*                 {}

<<EOF>>               {return FIN;}
.                     {fprintf(stderr, "Ligne %d : caractère invalide : %s\n", yylineno, yytext); exit(-1);}


%%
int yywrap(){
  return 1;
}


/*
 * Fonction auxiliaire qui donne le nom des différents tokens
 */

int token_fermes[] = 
{
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
  "AFFECTATION", 
  "PLUS", "MOINS", "FOIS", "DIVISION", "MODULO", 
  "EGALITE", "DIFFERENCE", "INFERIEUR_STRICT", "SUPERIEUR_STRICT", "INFERIEUR_LARGE", "SUPERIEUR_LARGE", 
  "ET", "OU", "NON", 
  "SI", "SINON", "TANT_QUE", "RETOURNER", 
  "ECRIRE", "LIRE", 
  "VIRGULE", "POINT_VIRGULE", "PARENTHESE_OUVRANTE", "PARENTHESE_FERMANTE", "ACCOLADE_OUVRANTE", "ACCOLADE_FERMANTE"
};

char *str_value[] = 
{
  "=", 
  "+", "-", "*", "/", "%", 
  "==", "!=", "<", ">", "<=", ">=", 
  "et", "ou", "non", 
  "si", "sinon", "tantque", "retourner", 
  "ecrire", "lire", 
  ",", ";", "(", ")", "{", "}"
};


int nbMotsClefs = 27;

void nom_token(int token, char *nom, char *valeur)
{   
  for (int i = 0; i < nbMotsClefs; i++)
  {
  	if (token == token_fermes[i])
    {
  	  strcpy(nom, str_token[i]);
  	  strcpy(valeur, "");
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
  else if (token == TYPE)
  {
    strcpy(nom, "type");
    strcpy(valeur, yytext);
  }
}


/* 
 * Fonction auxiliaire appelée par le compilateur en mode -l pour tester l'analyse
 * lexicale. Le fichier source doit être indiqué dans la variable globale yyin.
 * Cette fonction imprime le résultat de l'analyse lexicale sur la sortie standard.
 */
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