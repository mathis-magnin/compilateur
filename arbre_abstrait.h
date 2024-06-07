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
typedef struct n_argument n_argument;
typedef struct n_l_arguments n_l_arguments;

typedef struct n_programme n_programme;			  /* Noeud du type programme */
typedef struct n_l_instructions n_l_instructions; /* Noeud du type liste d'instructions */
typedef struct n_instruction n_instruction;		  /* Noeud du type liste instruction */
typedef struct n_ecrire n_ecrire;				  /* Noeud du type instruction ecrire */
typedef struct n_exp n_exp;						  /* Noeud du type expression (arithmétique) */
typedef struct n_operation n_operation;			  /* Noeud du type operation (arithmétique) */

typedef struct n_declaration n_declaration;
typedef struct n_affectation n_affectation;
typedef struct n_declaration_affectation n_declaration_affectation;
typedef struct n_cond_si n_cond_si;
typedef struct n_cond_sinon n_cond_sinon;
typedef struct n_cond_sinon_si n_cond_sinon_si;
typedef struct n_tant_que n_tant_que;
typedef struct n_retourner n_retourner;
typedef struct n_appel_fonction n_appel_fonction;

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

struct n_l_arguments
{
	n_argument *argument;
	n_l_arguments *arguments;
};

//

struct n_argument
{
	char *identifiant;
};

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
		i_ecrire,
		i_declaration,
		i_affectation,
		i_declaration_affectation,
		i_cond_si,
		i_cond_sinon,
		i_cond_sinon_si,
		i_tant_que,
		i_retourner,
		i_appel_fonction
	} type_instruction; // pour le moment une instruction peut-être uniquement de type écrire. Il faudra ajouter affectation, exécution de fonction, si,sinon, etc...
	union
	{
		n_exp *exp; // pour ecrire(exp);
		n_declaration *declaration;
		n_affectation *affectation;
		n_declaration_affectation *declaration_affectation;
		n_cond_si *cond_si;
		n_cond_sinon *cond_sinon;
		n_cond_sinon_si *cond_sinon_si;
		n_tant_que *tant_que;
		n_retourner *retourner;
		n_appel_fonction *appel_fonction;
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

struct n_declaration
{
	type type;
	char *identifiant;
};

//

struct n_affectation
{
	char *identifiant;
	n_exp *exp;
};

//

struct n_declaration_affectation
{
	type type;
	char *identifiant;
	n_exp *exp;
};

//

struct n_cond_si
{
	n_exp *exp;
	n_l_instructions *instructions;
};

//

struct n_cond_sinon
{
	n_l_instructions *instructions;
};

//

struct n_cond_sinon_si
{
	n_exp *exp;
	n_l_instructions *instructions;
};

//

struct n_tant_que
{
	n_exp *exp;
	n_l_instructions *instructions;
};

//

struct n_retourner
{
	n_exp *exp;
};

//

struct n_appel_fonction
{
	char *identifiant;
	n_l_arguments *arguments;
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

static const char type_op_value[] = {'+', '-', '*', '/', '%', 'e', 'd', '<', '>', 'i', 's', '|', '&', '!'};

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
void afficher_n_l_arguments(n_l_arguments *arguments, int indent);
void afficher_n_argument(n_argument *argument, int indent);

void afficher_n_programme(n_programme *prog, int indent);
void afficher_n_l_instructions(n_l_instructions *instructions, int indent);
void afficher_n_instruction(n_instruction *instruction, int indent);
void afficher_n_ecrire(n_ecrire *ecrire, int indent);
void afficher_n_declaration(n_declaration *declaration, int indent);
void afficher_n_affectation(n_affectation *affectation, int indent);
void afficher_n_declaration_affectation(n_declaration_affectation *declaration_affectation, int indent);
void afficher_n_cond_si(n_cond_si *cond_si, int indent);
void afficher_n_cond_sinon(n_cond_sinon *cond_sinon, int indent);
void afficher_n_cond_sinon_si(n_cond_sinon_si *cond_sinon_si, int indent);
void afficher_n_tant_que(n_tant_que *tant_que, int indent);
void afficher_n_retourner(n_retourner *retourner, int indent);
void afficher_n_appel_fonction(n_appel_fonction *appel_fonction, int indent);

void afficher_n_exp(n_exp *exp, int indent);
void afficher_n_operation(n_operation *operation, int indent);

/* Création */

n_l_fonctions *creer_n_l_fonctions(n_fonction *fonction, n_l_fonctions *fonctions);
n_fonction *creer_n_fonction(int type, char *identifiant, n_l_parametres *parametres, n_l_instructions *instructions);
n_l_parametres *creer_n_l_parametres(n_parametre *parametre, n_l_parametres *parametres);
n_parametre *creer_n_parametre(int type, char *identifiant);
n_l_arguments *creer_n_l_arguments(n_argument *argument, n_l_arguments *arguments);
n_argument *creer_n_argument(char *identifiant);

n_programme *creer_n_programme(n_l_fonctions *fonctions, n_l_instructions *instructions);
n_l_instructions *creer_n_l_instructions(n_instruction *instruction, n_l_instructions *instructions);
n_instruction *creer_n_ecrire(n_exp *exp);
n_instruction *creer_n_declaration(type type, char *identifiant);
n_instruction *creer_n_affectation(char *identifiant, n_exp *exp);
n_instruction *creer_n_declaration_affectation(type type, char *identifiant, n_exp *exp);
n_instruction *creer_n_cond_si(n_exp *exp, n_l_instructions *instructions);
n_instruction *creer_n_cond_sinon(n_l_instructions *instructions);
n_instruction *creer_n_cond_sinon_si(n_exp *exp, n_l_instructions *instructions);
n_instruction *creer_n_tant_que(n_exp *exp, n_l_instructions *instructions);
n_instruction *creer_n_retourner(n_exp *exp);
n_instruction *creer_n_appel_fonction(char *identifiant, n_l_arguments *arguments);

n_exp *creer_n_entier(int valeur);
n_exp *creer_n_booleen(int valeur);
n_exp *creer_n_operation(char type_operation, n_exp *exp1, n_exp *exp2);

#endif
