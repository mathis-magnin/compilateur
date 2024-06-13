#ifndef TABLE_DES_SYMBOLES_H
#define TABLE_DES_SYMBOLES_H

#include "arbre_abstrait.h" // Inclure arbre_abstrait.h pour la définition de type

typedef struct
{
    char *nom;
    type type_retour; // Utilisation du type défini dans arbre_abstrait.h
} Fonction;

typedef struct
{
    Fonction *fonctions;
    int taille;
    int capacite;
} TableSymboles;

TableSymboles *creer_table_symboles();
void ajouter_fonction(TableSymboles *table, const char *nom, type type_retour);
type obtenir_type_fonction(TableSymboles *table, const char *nom);
int fonction_existe(TableSymboles *table, const char *nom);
void liberer_table_symboles(TableSymboles *table);

#endif
