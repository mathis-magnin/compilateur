#ifndef __ARBRE_ABSTRAIT__
#define __ARBRE_ABSTRAIT__

/* Abbréviations:
 * n -> noeud
 * l -> liste
 * exp -> expression (arithmétique)
 */

/* Struct */

typedef struct n_programme n_programme; /* Noeud du type programme */

typedef struct n_l_fonctions n_l_fonctions;
typedef struct n_fonction n_fonction;
typedef struct n_l_parametres n_l_parametres;
typedef struct n_parametre n_parametre;

typedef struct n_exp n_exp;             /* Noeud du type expression */
typedef struct n_operation n_operation; /* Noeud du type operation */
typedef struct n_appel_fonction n_appel_fonction;
typedef struct n_l_arguments n_l_arguments;

typedef struct n_l_instructions n_l_instructions; /* Noeud du type liste d'instructions */
typedef struct n_instruction n_instruction;       /* Noeud du type liste instruction */
typedef struct n_variable n_variable;
typedef struct n_instr_cond n_instr_cond;

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

/* Déclaration de fonctions */

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

/* Instructions */

struct n_l_instructions
{
  n_instruction *instruction;
  n_l_instructions *instructions;
};

struct n_instruction
{
  enum
  {
    i_ecrire,

    i_declaration,
    i_affectation,
    i_declaration_affectation,

    i_si,
    i_sinon,
    i_sinon_si,
    i_tant_que,

    i_retourner
  } type_instruction;
  union
  {
    n_exp *exp; // pour "ecrire(exp);" et "retourner exp;"

    n_variable *variable;

    n_instr_cond *instr_cond;
  } u;
};

//

struct n_variable
{
  type type;
  char *identifiant;
  n_exp *exp;
};

//

struct n_instr_cond
{
  n_exp *exp;
  n_l_instructions *instructions;
};

/* Expressions */

struct n_exp
{
  enum
  {
    i_operation,

    i_entier,
    i_booleen,

    i_lire,
    i_appel_fonction,

    i_variable
  } type_exp;
  union
  {
    n_operation *operation;
    int valeur;
    n_appel_fonction *appel_fonction;
    n_variable *variable;
  } u;
};

struct n_appel_fonction
{
  type type;
  char *identifiant;
  n_l_arguments *arguments;
};

struct n_l_arguments
{
  n_exp *argument;
  n_l_arguments *arguments;
};

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

static const char type_op_value[] = {
    '+', '-', '*', '/', '%',
    'e', 'd', '<', '>', 'i', 's',
    '|', '&', '!'};

struct n_operation
{
  char type_operation;
  n_exp *exp1;
  n_exp *exp2;
};

/* Affichage */

void afficher_n_programme(n_programme *prog, int indent);

void afficher_n_l_fonctions(n_l_fonctions *fonctions, int indent);
void afficher_n_fonction(n_fonction *fonction, int indent);
void afficher_n_l_parametres(n_l_parametres *parametres, int indent);
void afficher_type(type type, int indent);
void afficher_identifiant(char *identifiant, int indent);
void afficher_n_parametre(n_parametre *parametre, int indent);

void afficher_n_l_instructions(n_l_instructions *instructions, int indent);
void afficher_n_instruction(n_instruction *instruction, int indent);
void afficher_n_exp(n_exp *exp, int indent);
void afficher_n_operation(n_operation *operation, int indent);
void afficher_n_appel_fonction(n_appel_fonction *appel_fonction, int indent);
void afficher_n_l_arguments(n_l_arguments *arguments, int indent);
void afficher_n_argument(n_exp *argument, int indent);

/* Création */

n_programme *creer_n_programme(n_l_fonctions *fonctions, n_l_instructions *instructions);

n_l_fonctions *creer_n_l_fonctions(n_l_fonctions *fonctions, n_fonction *fonction);
n_fonction *creer_n_fonction(int type, char *identifiant, n_l_parametres *parametres, n_l_instructions *instructions);
n_l_parametres *creer_n_l_parametres(n_parametre *parametre, n_l_parametres *parametres);
n_parametre *creer_n_parametre(int type, char *identifiant);

n_l_instructions *creer_n_l_instructions(n_instruction *instruction, n_l_instructions *instructions);
n_instruction *creer_n_ecrire(n_exp *exp);
n_instruction *creer_n_retourner(n_exp *exp);
n_instruction *creer_n_declaration(type type, char *identifiant, n_exp *exp);
n_instruction *creer_n_affectation(char *identifiant, n_exp *exp);
n_instruction *creer_n_instruction_conditionnelle(n_instruction *n, n_l_instructions *instructions);
n_instruction *creer_n_condition(n_instruction *n, n_exp *exp);
n_instruction *creer_n_si();
n_instruction *creer_n_sinon();
n_instruction *creer_n_sinon_si();
n_instruction *creer_n_tant_que();

n_exp *creer_n_entier(int valeur);
n_exp *creer_n_booleen(int valeur);
n_exp *creer_n_lire();
n_exp *creer_n_appel_fonc_ent(char *identifiant, n_l_arguments *arguments);
n_exp *creer_n_appel_fonc_bool(char *identifiant, n_l_arguments *arguments);
n_l_arguments *creer_n_l_arguments(n_l_arguments *arguments, n_exp *argument);
n_exp *creer_n_operation(char type_operation, n_exp *exp1, n_exp *exp2);
n_exp *creer_n_variable_entiere(char *identifiant);
n_exp *creer_n_variable_booleenne(char *identifiant);

#endif