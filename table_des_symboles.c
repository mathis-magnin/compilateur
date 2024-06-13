#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table_des_symboles.h"

#define TAILLE_INITIALE 10

TableSymboles *creer_table_symboles()
{
    TableSymboles *table = (TableSymboles *)malloc(sizeof(TableSymboles));
    table->fonctions = (Fonction *)malloc(TAILLE_INITIALE * sizeof(Fonction));
    table->taille = 0;
    table->capacite = TAILLE_INITIALE;
    return table;
}

void ajouter_fonction(TableSymboles *table, const char *nom, TypeRetour type)
{
    if (table->taille >= table->capacite)
    {
        table->capacite *= 2;
        table->fonctions = (Fonction *)realloc(table->fonctions, table->capacite * sizeof(Fonction));
    }
    table->fonctions[table->taille].nom = strdup(nom);
    table->fonctions[table->taille].type = type;
    table->taille++;
}

TypeRetour obtenir_type_fonction(TableSymboles *table, const char *nom)
{
    for (int i = 0; i < table->taille; i++)
    {
        if (strcmp(table->fonctions[i].nom, nom) == 0)
        {
            return table->fonctions[i].type;
        }
    }
    fprintf(stderr, "Erreur : Fonction %s non trouvée\n", nom);
    exit(1);
}

int fonction_existe(TableSymboles *table, const char *nom)
{
    for (int i = 0; i < table->taille; i++)
    {
        if (strcmp(table->fonctions[i].nom, nom) == 0)
        {
            return 1;
        }
    }
    return 0;
}

void liberer_table_symboles(TableSymboles *table)
{
    for (int i = 0; i < table->taille; i++)
    {
        free(table->fonctions[i].nom);
    }
    free(table->fonctions);
    free(table);
}
