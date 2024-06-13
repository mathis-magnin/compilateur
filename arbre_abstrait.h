#ifndef __ARBRE_ABSTRAIT__
#define __ARBRE_ABSTRAIT__

/* Abbréviations:
 * n -> noeud
 * l -> liste
 * exp -> expression (arithmétique)
 */

/* Struct */

typedef struct n_l_fonctions n_l_fonctions;
typedef struct n_fonction n_fonction;
typedef struct n_l_parametres n_l_parametres;
typedef struct n_parametre n_parametre;

typedef struct n_programme n_programme;           /* Noeud du type programme */
typedef struct n_l_instructions n_l_instructions; /* Noeud du type liste d'instructions */
typedef struct n_instruction n_instruction;       /* Noeud du type liste instruction */
typedef struct n_ecrire n_ecrire;                 /* Noeud du type instruction ecrire */
typedef struct n_exp n_exp;                       /* Noeud du type expression (arithmétique) */
typedef struct n_operation n_operation;           /* Noeud du type operation (arithmétique) */

//

typedef enum
{
  TYPE_ENTIER,
  TYPE_BOOLEEN
} type;

//

struct n_programme
{
  n_l_fonctions *fonctions;
  n_l_instructions *instructions;
};

/* Fonctions */

struct n_l_fonctions
{
  n_fonction *fonction;
  n_l_fonctions *fonctions;
};

//

struct n_fonction
{
  type type;
  char *identifiant;
  n_l_parametres *parametres;
  n_l_instructions *instructions;
};

//

struct n_l_parametres
{
  n_parametre *parametre;
  n_l_parametres *parametres;
};

//

struct n_parametre
{
  type type;
  char *identifiant;
};

//

/* Instructions */

struct n_l_instructions
{
  n_instruction *instruction;
  n_l_instructions *instructions;
};

//

struct n_instruction
{
  enum
  {
    i_ecrire
  } type_instruction; // pour le moment une instruction peut-être uniquement de type écrire. Il faudra ajouter affectation, exécution de fonction, si,sinon, etc...
  union
  {
    n_exp *exp; // pour ecrire(exp);
  } u;
};

//

struct n_exp
{
  enum
  {
    i_operation,
    i_entier,
    i_booleen
  } type_exp;
  union
  {
    n_operation *operation;
    int valeur;
  } u;
};

//

typedef enum
{
  i_plus,
  i_moins,
  i_fois,
  i_division,
  i_modulo,

  i_egalite,
  i_difference,
  i_inferieur_strict,
  i_superieur_strict,
  i_inferieur_large,
  i_superieur_large,

  i_ou,
  i_et,
  i_non
} type_op;

static const char type_op_value[] =
    {
        '+', '-', '*', '/', '%',
        'e', 'd', '<', '>', 'i', 's',
        '|', '&', '!'};

struct n_operation
{
  char type_operation;
  n_exp *exp1;
  n_exp *exp2;
};

//

/* Affichage */

void afficher_n_l_fonctions(n_l_fonctions *fonctions, int indent);
void afficher_n_fonction(n_fonction *fonction, int indent);
void afficher_n_l_parametres(n_l_parametres *parametres, int indent);
void afficher_type_declaration(type type, int indent);
void afficher_identifiant(char *identifiant, int indent);
void afficher_n_parametre(n_parametre *parametre, int indent);

void afficher_n_programme(n_programme *prog, int indent);
void afficher_n_l_instructions(n_l_instructions *instructions, int indent);
void afficher_n_instruction(n_instruction *instruction, int indent);
void afficher_n_ecrire(n_ecrire *ecrire, int indent);
void afficher_n_exp(n_exp *exp, int indent);
void afficher_n_operation(n_operation *operation, int indent);

/* Création */

n_l_fonctions *creer_n_l_fonctions(n_fonction *fonction, n_l_fonctions *fonctions);
n_fonction *creer_n_fonction(int type, char *identifiant, n_l_parametres *parametres, n_l_instructions *instructions);
n_l_parametres *creer_n_l_parametres(n_parametre *parametre, n_l_parametres *parametres);
n_parametre *creer_n_parametre(int type, char *identifiant);

n_programme *creer_n_programme(n_l_fonctions *fonctions, n_l_instructions *instructions);
n_l_instructions *creer_n_l_instructions(n_instruction *instruction, n_l_instructions *instructions);
n_instruction *creer_n_ecrire(n_exp *exp);
n_exp *creer_n_entier(int valeur);
n_exp *creer_n_booleen(int valeur);
n_exp *creer_n_operation(char type_operation, n_exp *exp1, n_exp *exp2);

#endif
