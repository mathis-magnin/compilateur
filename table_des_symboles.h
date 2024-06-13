#ifndef TABLE_DES_SYMBOLES_H
#define TABLE_DES_SYMBOLES_H

typedef enum
{
    FONCTION_ENTIER,
    FONCTION_BOOLEEN
} TypeRetour;
typedef struct
{
    char *nom;
    TypeRetour type;
} Fonction;

typedef struct
{
    Fonction *fonctions;
    int taille;
    int capacite;
} TableSymboles;

TableSymboles *creer_table_symboles();
void ajouter_fonction(TableSymboles *table, const char *nom, TypeRetour type);
TypeRetour obtenir_type_fonction(TableSymboles *table, const char *nom);
int fonction_existe(TableSymboles *table, const char *nom);
void liberer_table_symboles(TableSymboles *table);

#endif
