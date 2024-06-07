#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arbre_abstrait.h"

/* Abbréviations:
 * n -> noeud
 * l -> liste
 */

/* Affichage */

// affiche l'entier avec sa valeur après un certain nombres d'espaces et un retour à la ligne
void afficher(char *s, int indent)
{
	for (int i = 0; i < indent; i++)
	{
		printf(" ");
	}
	printf("%s\n", s);
}

//

// affiche l'entier avec sa valeur après un certain nombres d'espaces
void afficher_caractere(char c, int indent)
{
	for (int i = 0; i < indent; i++)
	{
		printf(" ");
	}
	printf("%c\n", c);
}

//

// affiche la chaine de caractère s après un certain nombres d'espaces
void afficher_entier(int valeur, int indent)
{
	for (int i = 0; i < indent; i++)
	{
		printf(" ");
	}
	printf("[Entier: %d]\n", valeur);
}

//

void afficher_booleen(int valeur, int indent)
{
	for (int i = 0; i < indent; i++)
	{
		printf(" ");
	}
	printf("[Booléen: %s]\n", (valeur == 1) ? "Vrai" : "Faux");
}

//

void afficher_n_programme(n_programme *prog, int indent)
{
	afficher("<programme>", indent);
	afficher_n_l_fonctions(prog->fonctions, indent + 1);
	afficher_n_l_instructions(prog->instructions, indent + 1);
	afficher("</programme>", indent);
}

//

void afficher_type(type type, int indent)
{

	for (int i = 0; i < indent; i++)
	{
		printf(" ");
	}
	printf("[Type: %s]\n", (type == TYPE_BOOLEEN) ? "Booléen" : "Entier");
}

//

void afficher_n_l_fonctions(n_l_fonctions *fonctions, int indent)
{
	afficher("<liste_fonctions>", indent);

	while (fonctions != NULL)
	{
		if (fonctions->fonction != NULL)
		{
			afficher_n_fonction(fonctions->fonction, indent + 1);
		}
		fonctions = fonctions->fonctions;
	}

	afficher("</liste_fonctions>", indent);
}

//

void afficher_n_fonction(n_fonction *fonction, int indent)
{
	afficher("<fonction>", indent);

	afficher_type(fonction->type, indent + 1);
	afficher_identifiant(fonction->identifiant, indent + 1);
	afficher_n_l_parametres(fonction->parametres, indent + 1);
	afficher_n_l_instructions(fonction->instructions, indent + 1);

	afficher("</fonction>", indent);
}

//

void afficher_identifiant(char *identifiant, int indent)
{

	for (int i = 0; i < indent; i++)
	{
		printf(" ");
	}
	printf("[Identifiant: %s]\n", identifiant);
}

//

void afficher_n_l_parametres(n_l_parametres *parametres, int indent)
{
	afficher("<liste_parametres>", indent);

	while (parametres != NULL)
	{
		if (parametres->parametre != NULL)
		{
			afficher_n_parametre(parametres->parametre, indent + 1);
		}
		parametres = parametres->parametres;
	}

	afficher("</liste_parametres>", indent);
}

//

void afficher_n_parametre(n_parametre *parametre, int indent)
{
	afficher("<parametre>", indent);

	afficher_type(parametre->type, indent + 1);
	afficher_identifiant(parametre->identifiant, indent + 1);

	afficher("</parametre>", indent);
}

//

void afficher_n_l_arguments(n_l_arguments *arguments, int indent)
{
	afficher("<liste_arguments>", indent);

	while (arguments != NULL)
	{
		if (arguments->argument != NULL)
		{
			afficher_n_argument(arguments->argument, indent + 1);
		}
		arguments = arguments->arguments;
	}

	afficher("</git stuments>", indent);
}

//

void afficher_n_argument(n_argument *argument, int indent)
{
	afficher("<argument>", indent);

	afficher_identifiant(argument->identifiant, indent + 1);

	afficher("</argument>", indent);
}

//

void afficher_n_l_instructions(n_l_instructions *instructions, int indent)
{
	afficher("<liste_instuctions>", indent);

	do
	{
		if (instructions->instruction != NULL)
		{
			afficher_n_instruction(instructions->instruction, indent + 1);
		}
		instructions = instructions->instructions;
	} while (instructions != NULL);
	afficher("</liste_instructions>", indent);
}

//

void afficher_n_instruction(n_instruction *instruction, int indent)
{
	if (instruction->type_instruction == i_ecrire)
	{
		afficher("<ecrire>", indent);
		afficher_n_exp(instruction->u.exp, indent + 1);
		afficher("</ecrire>", indent);
	}
	if (instruction->type_instruction == i_declaration)
	{
		afficher("<declaration>", indent);
		afficher_type(instruction->u.declaration->type, indent + 1);
		afficher_identifiant(instruction->u.declaration->identifiant, indent + 1);
		afficher("</declaration>", indent);
	}
	if (instruction->type_instruction == i_affectation)
	{
		afficher("<affectation>", indent);
		afficher_identifiant(instruction->u.affectation->identifiant, indent + 1);
		afficher_n_exp(instruction->u.affectation->exp, indent + 1);
		afficher("</affectation>", indent);
	}
	if (instruction->type_instruction == i_cond_si)
	{
		afficher("<cond_si>", indent);
		afficher_n_exp(instruction->u.cond_si->exp, indent + 1);
		afficher_n_l_instructions(instruction->u.cond_si->instructions, indent + 1);
		afficher("</cond_si>", indent);
	}
	if (instruction->type_instruction == i_cond_sinon)
	{
		afficher("<cond_sinon>", indent);
		afficher_n_l_instructions(instruction->u.cond_sinon->instructions, indent + 1);
		afficher("</cond_sinon>", indent);
	}
	if (instruction->type_instruction == i_cond_sinon_si)
	{
		afficher("<cond_sinon_si>", indent);
		afficher_n_exp(instruction->u.cond_sinon_si->exp, indent + 1);
		afficher_n_l_instructions(instruction->u.cond_sinon_si->instructions, indent + 1);
		afficher("</cond_sinon_si>", indent);
	}
	if (instruction->type_instruction == i_tant_que)
	{
		afficher("<tant_que>", indent);
		afficher_n_exp(instruction->u.tant_que->exp, indent + 1);
		afficher_n_l_instructions(instruction->u.tant_que->instructions, indent + 1);
		afficher("</tant_que>", indent);
	}
	if (instruction->type_instruction == i_retourner)
	{
		afficher("<retourner>", indent);
		afficher_n_exp(instruction->u.retourner->exp, indent + 1);
		afficher("</retourner>", indent);
	}
	if (instruction->type_instruction == i_appel_fonction)
	{
		afficher("<appel_fonction>", indent);
		afficher_identifiant(instruction->u.appel_fonction->identifiant, indent + 1);
		afficher_n_l_arguments(instruction->u.appel_fonction->arguments, indent + 1);
		afficher("</appel_fonction>", indent);
	}
}

//

void afficher_n_exp(n_exp *exp, int indent)
{
	if (exp->type_exp == i_operation)
	{
		afficher_n_operation(exp->u.operation, indent);
	}
	else if (exp->type_exp == i_entier)
	{
		afficher_entier(exp->u.valeur, indent);
	}
	else if (exp->type_exp == i_booleen)
	{
		afficher_booleen(exp->u.valeur, indent);
	}
}

//

void afficher_n_operation(n_operation *operation, int indent)
{
	afficher("<operation>", indent);
	afficher_n_exp(operation->exp1, indent + 1);
	afficher_caractere(operation->type_operation, indent + 1);
	if (operation->exp2 != NULL)
	{
		afficher_n_exp(operation->exp2, indent + 1);
	}
	afficher("</operation>", indent);
}

//

/* Creation */

n_programme *creer_n_programme(n_l_fonctions *fonctions, n_l_instructions *instructions)
{
	n_programme *n = malloc(sizeof(n_programme));

	n->fonctions = fonctions;
	n->instructions = instructions;

	return n;
}

//

n_l_instructions *creer_n_l_instructions(n_instruction *instruction, n_l_instructions *instructions)
{
	n_l_instructions *n = malloc(sizeof(n_l_instructions));

	n->instruction = instruction;
	n->instructions = instructions;

	return n;
}

//

n_instruction *creer_n_ecrire(n_exp *exp)
{
	n_instruction *n = malloc(sizeof(n_instruction));

	n->type_instruction = i_ecrire;
	n->u.exp = exp;

	return n;
}

//

n_exp *creer_n_operation(char type_operation, n_exp *exp1, n_exp *exp2)
{
	n_exp *n = malloc(sizeof(n_exp));
	n_operation *n_op = malloc(sizeof(n_operation));

	n->u.operation = n_op;
	n->type_exp = i_operation;
	n_op->type_operation = type_operation;
	n_op->exp1 = exp1;
	n_op->exp2 = exp2;

	return n;
}

//

n_exp *creer_n_entier(int valeur)
{
	n_exp *n = malloc(sizeof(n_exp));

	n->type_exp = i_entier;
	n->u.valeur = valeur;

	return n;
}

n_exp *creer_n_booleen(int valeur)
{
	n_exp *n = malloc(sizeof(n_exp));
	n->type_exp = i_booleen;
	n->u.valeur = valeur;
	return n;
}

// CHANGEMENTS

n_l_fonctions *creer_n_l_fonctions(n_fonction *fonction, n_l_fonctions *fonctions)
{
	n_l_fonctions *n = malloc(sizeof(n_l_fonctions));

	n->fonction = fonction;
	n->fonctions = fonctions;

	return n;
}

//

n_fonction *creer_n_fonction(int type, char *identifiant, n_l_parametres *parametres, n_l_instructions *instructions)
{
	n_fonction *n = malloc(sizeof(n_fonction));

	n->type = type ? TYPE_BOOLEEN : TYPE_ENTIER;
	n->identifiant = malloc(sizeof(char) * strlen(identifiant));
	strcpy(n->identifiant, identifiant);
	n->parametres = parametres;
	n->instructions = instructions;

	return n;
}

//

n_l_parametres *creer_n_l_parametres(n_parametre *parametre, n_l_parametres *parametres)
{
	n_l_parametres *n = malloc(sizeof(n_l_parametres));

	n->parametre = parametre;
	n->parametres = parametres;

	return n;
}

//

n_parametre *creer_n_parametre(int type, char *identifiant)
{
	n_parametre *n = malloc(sizeof(n_parametre));

	n->type = type ? TYPE_BOOLEEN : TYPE_ENTIER;
	n->identifiant = malloc(sizeof(char) * strlen(identifiant));
	strcpy(n->identifiant, identifiant);

	return n;
}

//

n_l_arguments *creer_n_l_arguments(n_argument *argument, n_l_arguments *arguments)
{
	n_l_arguments *n = malloc(sizeof(n_l_arguments));

	n->argument = argument;
	n->arguments = arguments;

	return n;
}

//

n_argument *creer_n_argument(char *identifiant)
{
	n_argument *n = malloc(sizeof(n_argument));

	n->identifiant = malloc(sizeof(char) * strlen(identifiant));
	strcpy(n->identifiant, identifiant);

	return n;
}

//

n_instruction *creer_n_declaration(type type, char *identifiant)
{
	n_instruction *n = malloc(sizeof(n_instruction));

	n->type_instruction = i_declaration;
	n->u.declaration = malloc(sizeof(n_declaration));
	n->u.declaration->type = type ? TYPE_BOOLEEN : TYPE_ENTIER;
	n->u.declaration->identifiant = malloc(sizeof(char) * strlen(identifiant));
	strcpy(n->u.declaration->identifiant, identifiant);

	return n;
}

//

n_instruction *creer_n_affectation(char *identifiant, n_exp *exp)
{
	n_instruction *n = malloc(sizeof(n_instruction));

	n->type_instruction = i_affectation;
	n->u.affectation = malloc(sizeof(n_affectation));
	n->u.affectation->identifiant = malloc(sizeof(char) * strlen(identifiant));
	strcpy(n->u.affectation->identifiant, identifiant);
	n->u.affectation->exp = exp;

	return n;
}

//

n_instruction *creer_n_declaration_affectation(type type, char *identifiant, n_exp *exp)
{
	n_instruction *n = malloc(sizeof(n_instruction));

	n->type_instruction = i_declaration_affectation;
	n->u.declaration_affectation = malloc(sizeof(n_declaration_affectation));
	n->u.declaration_affectation->type = type ? TYPE_BOOLEEN : TYPE_ENTIER;
	n->u.declaration_affectation->identifiant = malloc(sizeof(char) * strlen(identifiant));
	strcpy(n->u.declaration_affectation->identifiant, identifiant);
	n->u.declaration_affectation->exp = exp;

	return n;
}

//

n_instruction *creer_n_cond_si(n_exp *exp, n_l_instructions *instructions)
{
	n_instruction *n = malloc(sizeof(n_instruction));

	n->type_instruction = i_cond_si;
	n->u.cond_si = malloc(sizeof(n_cond_si));
	n->u.cond_si->exp = exp;
	n->u.cond_si->instructions = instructions;

	return n;
}

//

n_instruction *creer_n_cond_sinon(n_l_instructions *instructions)
{
	n_instruction *n = malloc(sizeof(n_instruction));

	n->type_instruction = i_cond_sinon;
	n->u.cond_sinon = malloc(sizeof(n_cond_sinon));
	n->u.cond_sinon->instructions = instructions;

	return n;
}

//

n_instruction *creer_n_cond_sinon_si(n_exp *exp, n_l_instructions *instructions)
{
	n_instruction *n = malloc(sizeof(n_instruction));

	n->type_instruction = i_cond_sinon_si;
	n->u.cond_sinon_si = malloc(sizeof(n_cond_sinon_si));
	n->u.cond_sinon_si->exp = exp;
	n->u.cond_sinon_si->instructions = instructions;

	return n;
}

//

n_instruction *creer_n_tant_que(n_exp *exp, n_l_instructions *instructions)
{
	n_instruction *n = malloc(sizeof(n_instruction));

	n->type_instruction = i_tant_que;
	n->u.tant_que = malloc(sizeof(n_tant_que));
	n->u.tant_que->exp = exp;
	n->u.tant_que->instructions = instructions;

	return n;
}

//

n_instruction *creer_n_retourner(n_exp *exp)
{
	n_instruction *n = malloc(sizeof(n_instruction));

	n->type_instruction = i_retourner;
	n->u.retourner = malloc(sizeof(n_retourner));
	n->u.retourner->exp = exp;

	return n;
}

//

n_instruction *creer_n_appel_fonction(char *identifiant, n_l_arguments *arguments)
{
	n_instruction *n = malloc(sizeof(n_instruction));

	n->type_instruction = i_appel_fonction;
	n->u.appel_fonction = malloc(sizeof(n_appel_fonction));
	n->u.appel_fonction->identifiant = malloc(sizeof(char) * strlen(identifiant));
	strcpy(n->u.appel_fonction->identifiant, identifiant);
	n->u.appel_fonction->arguments = arguments;

	return n;
}
