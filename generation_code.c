#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbre_abstrait.h"
#include "generation_code.h"

// pour afficher le code uniquement si l'option afficher_arm vaut 1
#define printifm(format, ...)    \
  if (afficher_arm)              \
  {                              \
    printf(format, __VA_ARGS__); \
  }

int afficher_arm = 1;

/* fonction locale, permet d'afficher un commentaire */
void arm_comment(char *comment)
{
  if (comment != NULL)
  {
    printifm("\t\t @ %s", comment); // le point virgule indique le début d'un commentaire en arm. Les tabulations sont là pour faire jolie.
  }
  printifm("%s", "\n");
}

/*
Affiche une commande arm sur une ligne
Par convention, les derniers opérandes sont nuls si l'opération a moins de 3 arguments.
*/
void arm_instruction(char *opcode, char *op1, char *op2, char *op3, char *comment)
{
  printifm("\t%s", opcode);
  if (op1 != NULL)
  {
    printifm("\t%s", op1);
    if (op2 != NULL)
    {
      printifm(", %s", op2);
      if (op3 != NULL)
      {
        printifm(", %s", op3);
      }
    }
  }
  arm_comment(comment);
}

int num_etiquette_courante = 0;
void nouveau_nom_etiquette(char *etiq)
{
  sprintf(etiq, ".e%d", num_etiquette_courante++);
}

char *malloc_etiquette()
{
  int c = 0;
  int number = num_etiquette_courante;
  do
  {
    c++;
  } while ((number /= 10) > 0);
  return malloc(sizeof(char) * (c + 4));
}

/* Fonctions de génération du code */

void gen_prog(n_programme *n)
{
  printifm("%s", ".LC0:\n");
  printifm("%s", "	.ascii	\"%d\\000\"\n");
  printifm("%s", "	.align	2\n");
  printifm("%s", ".LC1:\n");
  printifm("%s", "	.ascii	\"%d\\012\\000\"\n");
  printifm("%s", "	.text\n");
  printifm("%s", "	.align	2\n");
  printifm("%s", "	.global	main\n");
  printifm("%s", "main:\n");
  arm_instruction("push", "{fp,lr}", NULL, NULL, NULL);
  arm_instruction("add", "fp", "sp", "#4", NULL);
  gen_liste_instructions(n->instructions);
  arm_instruction("mov", "r0", "#0", NULL, NULL);
  arm_instruction("pop", "{fp, pc}", NULL, NULL, NULL);
}

/* Instructions */

void gen_liste_instructions(n_l_instructions *n)
{
  do
  {
    if (n->instruction != NULL)
    {
      gen_instruction(n->instruction);
    }
    n = n->instructions;
  } while (n != NULL);
}

void gen_instruction(n_instruction *n)
{
  switch (n->type_instruction)
  {
  case i_ecrire:
    gen_exp(n->u.exp);                                // on calcule et empile la valeur de l'expression
    arm_instruction("pop", "{r1}", NULL, NULL, NULL); // on dépile la valeur d'expression sur r1
    arm_instruction("ldr", "r0", "=.LC1", NULL, NULL);
    arm_instruction("bl", "printf", NULL, NULL, NULL); // on envoie la valeur de r1 sur la sortie standard
    break;

    // case i_declaration:
    // case i_affectation:
    // case i_declaration_affectation:

  case i_si:
  case i_sinon_si:
    gen_si(n->u.instr_cond);
    break;

  case i_sinon:
    gen_liste_instructions(n->u.instr_cond->instructions);
    break;

  case i_tant_que:
    gen_tant_que(n->u.instr_cond);
    break;

    // case i_retourner:

  default:
    fprintf(stderr, "génération type instruction non implémenté\n");
    exit(1);
  }
}

/* Expression */

void gen_exp(n_exp *n)
{
  char buffer[12];
  switch (n->type_exp)
  {
  case i_operation:
    gen_operation(n->u.operation);
    break;

  case i_entier:
    sprintf(buffer, "#%d", n->u.valeur);
    arm_instruction("mov", "r1", buffer, NULL, NULL);  // on met sur la pile la valeur entière
    arm_instruction("push", "{r1}", NULL, NULL, NULL); // on met sur la pile la valeur entière
    break;

  case i_booleen:
    sprintf(buffer, "#%d", n->u.valeur);
    arm_instruction("mov", "r1", buffer, NULL, NULL);  // on met sur la pile la valeur booléenne
    arm_instruction("push", "{r1}", NULL, NULL, NULL); // on met sur la pile la valeur booléenne
    break;

  case i_lire:
    arm_instruction("ldr", "r0", "=.LC1", NULL, NULL);
    arm_instruction("sub", "sp", "sp", "#4", "effectue l'opération sp-4 et stocke le résultat dans sp");
    arm_instruction("mov", "r1", "sp", NULL, NULL);   // Copie l'adresse de sp dans r1
    arm_instruction("bl", "scanf", NULL, NULL, NULL); // on récupère les infos de l'entrée standard
    arm_instruction("pop", "{r1}", NULL, NULL, "dépilé dans r1");
    arm_instruction("push", "{r1}", NULL, NULL, NULL);
    break;

    // case i_appel_fonction:
    // case i_variable:

  default:
    fprintf(stderr, "génération type expression non implémenté\n");
    exit(1);
    break;
  }
}

/* Opération */

void gen_operation(n_operation *n)
{
  if (n->exp1 != NULL)
  {
    gen_exp(n->exp1); // on calcule et empile la valeur de exp1
  }
  if (n->exp2 != NULL)
  {
    gen_exp(n->exp2); // on calcule et empile la valeur de exp2
    arm_instruction("pop", "{r1}", NULL, NULL, "dépile exp2 dans r1");
  }
  if (n->exp1 != NULL)
  {
    // ici core dumped lors d'un appel à not
    arm_instruction("pop", "{r0}", NULL, NULL, "dépile exp1 dans r0");
  }

  /* Vérification de type */
  switch (n->type_operation)
  {
  /* opération arithmétiques */
  case '+':
  case '-':
  case '*':
  case '/':
  case '%':
    if (n->exp1 == NULL || n->exp2 == NULL)
    {
      fprintf(stderr, "L'une des deux opérandes est NULL");
      exit(1);
      return;
    }
    else
    {
      if (n->exp1->type_exp != i_operation && n->exp2->type_exp != i_operation)
      {
        if (n->exp1->type_exp != i_entier || n->exp2->type_exp != i_entier)
        {
          fprintf(stderr, "Premier morceau de l'expression : %c\n", n->exp1->u.operation->type_operation);
          fprintf(stderr, "Second morceau de l'expression : %d\n", n->exp2->u.valeur);
          fprintf(stderr, "Erreur de typage, un booléen ou plus pour une opération entière");
          exit(1);
          return;
        }
      }
    }

    gen_operation_entiere(n);
    break;

  /* opérations de comparaison */
  case 'e':
  case 'd':
    if (n->exp1 == NULL || n->exp2 == NULL)
    {
      fprintf(stderr, "L'une des deux opérandes est NULL");
      exit(1);
      return;
    }
    else
    {
      if (n->exp1->type_exp != i_operation && n->exp2->type_exp != i_operation)
      {
        if (n->exp1->type_exp != n->exp2->type_exp)
        {
          fprintf(stderr, "Premier morceau de l'expression : %c\n", n->exp1->u.operation->type_operation);
          fprintf(stderr, "Second morceau de l'expression : %d\n", n->exp2->u.valeur);
          fprintf(stderr, "Erreur de typage, comparaison entre deux éléments de type différents");
          exit(1);
          return;
        }
      }
    }

    gen_comparaison(n);
    break;
  case '<':
  case '>':
  case 'i':
  case 's':
    if (n->exp1 == NULL || n->exp2 == NULL)
    {
      fprintf(stderr, "L'une des deux opérandes est NULL");
      exit(1);
      return;
    }
    else
    {
      if (n->exp1->type_exp != i_operation && n->exp2->type_exp != i_operation)
      {
        if (n->exp1->type_exp != i_entier || n->exp2->type_exp != i_entier)
        {
          fprintf(stderr, "Erreur de typage, comparaison d'ordre entre deux éléments de type différents");
          exit(1);
          return;
        }
      }
    }

    gen_comparaison(n);
    break;

  /* opérations booléennes */
  case '|':
  case '&':
    if (n->exp1 == NULL || n->exp2 == NULL)
    {
      fprintf(stderr, "L'une des deux opérandes est NULL");
      exit(1);
      return;
    }
    else
    {
      if (n->exp1->type_exp != i_operation && n->exp2->type_exp != i_operation)
      {
        if (n->exp1->type_exp != i_booleen || n->exp2->type_exp != i_booleen)
        {
          fprintf(stderr, "Erreur de typage, un entier ou plus pour une opération booléenne");
          exit(1);
          return;
        }
      }
    }
    gen_operation_booleenne(n);
    break;

  case '!':
    if (n->exp1 == NULL || (n->exp1 != NULL && n->exp2 != NULL))
    {
      fprintf(stderr, "Argumentation invalide");
      exit(1);
      return;
    }
    gen_operation_booleenne(n);
    break;

  /* opérations non implémentées */
  default:
    fprintf(stderr, "génération opération %d non implémenté\n", n->type_operation);
    exit(1);
  }
}

void gen_operation_entiere(n_operation *n)
{

  // Déclaration de __aeabi_idiv
  asm(".global __aeabi_idiv");
  // Déclaration de __aeabi_idivmod
  asm(".global __aeabi_idivmod");
  switch (n->type_operation)
  {
  case '+':
    arm_instruction("add", "r0", "r1", "r0", "effectue l'opération r0+r1");
    // le résultat est stocké dans r0
    arm_instruction("push", "{r0}", NULL, NULL, "empile le résultat");
    break;

  case '-':
    arm_instruction("sub", "r0", "r0", "r1", "effectue l'opération r0-r1");
    // le résultat est stocké dans r0
    arm_instruction("push", "{r0}", NULL, NULL, "empile le résultat");
    break;

  case '*':
    arm_instruction("mul", "r0", "r1", "r0", "effectue l'opération r0*r1");
    // le résultat est stocké dans r0
    arm_instruction("push", "{r0}", NULL, NULL, "empile le résultat");
    break;

  case '/':
    arm_instruction("bl ", "__aeabi_idiv", NULL, NULL, "");
    // le résultat est stocké dans r0
    arm_instruction("push", "{r0}", NULL, NULL, "empile le résultat");
    break;

  case '%':
    arm_instruction("bl ", "__aeabi_idivmod", NULL, NULL, "");
    // le résultat est stocké dans r1
    arm_instruction("push", "{r1}", NULL, NULL, "empile le résultat");
    break;
  }
}

void gen_operation_booleenne(n_operation *n)
{
  char *etiquette_vrai = malloc_etiquette();
  char *etiquette_fin = malloc_etiquette();
  nouveau_nom_etiquette(etiquette_vrai);
  nouveau_nom_etiquette(etiquette_fin);

  // Déclaration de __aeabi_idivmod
  asm(".global __aeabi_idivmod");

  switch (n->type_operation)
  {
  case '|':
    arm_instruction("add", "r0", "r0", "r1", "effectue l'opération r0+r1");
    // le résultat est stocké dans r0
    arm_instruction("push", "{r0}", NULL, NULL, "empile le résultat");
    arm_instruction("pop", "{r0}", NULL, NULL, "dépile dans r0");
    arm_instruction("cmp", "r0", "#1", NULL, "compare r0 à 1 (r0-1)");
    // le résultat est stocké dans r0
    arm_instruction("push", "{r0}", NULL, NULL, "empile le résultat");
    arm_instruction("pop", "{r0}", NULL, NULL, "dépile dans r0");
    // si le résultat de la comparaison est strictement négatif
    arm_instruction("movlt", "r0", "#0", NULL, "si le résultat est strictement négatif, affecte 0 à r0");
    // si le résultat de la comparaison est supérieur ou égal à 0
    arm_instruction("movge", "r0", "#1", NULL, "sinon, affecte 1 à r0");
    arm_instruction("push", "{r0}", NULL, NULL, "empile le résultat");
    break;

  case '&':
    arm_instruction("mul", "r0", "r0", "r1", "effectue l'opération r0*r1");
    // le résultat est stocké dans r0
    arm_instruction("push", "{r0}", NULL, NULL, "empile le résultat");
    break;

  case '!':
    arm_instruction("eor", "r0", "r0", "#1", "effectue l'opération r0 XOR #1");
    // le résultat est stocké dans r0
    arm_instruction("push", "{r0}", NULL, NULL, "empile le résultat");
    break;
  }
}

void gen_comparaison(n_operation *n)
{
  arm_instruction("cmp", "r0", "r1", NULL, "effectue l'opération de comparaison");

  char *etiquette_vrai = malloc_etiquette();
  char *etiquette_fin = malloc_etiquette();
  nouveau_nom_etiquette(etiquette_vrai);
  nouveau_nom_etiquette(etiquette_fin);

  switch (n->type_operation)
  {
  case 'e':
    arm_instruction("beq", etiquette_vrai, NULL, NULL, "déplace le compteur de programme à la partie vrai");
    break;

  case 'd':
    arm_instruction("bne", etiquette_vrai, NULL, NULL, "déplace le compteur de programme à la partie vrai");
    break;

  case '<':
    arm_instruction("blt", etiquette_vrai, NULL, NULL, "déplace le compteur de programme à la partie vrai");
    break;

  case '>':
    arm_instruction("bgt", etiquette_vrai, NULL, NULL, "déplace le compteur de programme à la partie vrai");
    break;

  case 'i':
    arm_instruction("ble", etiquette_vrai, NULL, NULL, "déplace le compteur de programme à la partie vrai");
    break;

  case 's':
    arm_instruction("bge", etiquette_vrai, NULL, NULL, "déplace le compteur de programme à la partie vrai");
    break;
  }

  /* Faux */
  arm_instruction("mov", "r0", "#0", NULL, "affecte 0 à r0");
  arm_instruction("b", etiquette_fin, NULL, NULL, "déplace le compteur de programme à la partie fin");

  /* Vrai */
  arm_instruction(strcat(etiquette_vrai, ":"), NULL, NULL, NULL, "etiquette vrai");
  arm_instruction("mov", "r0", "#1", NULL, "affecte 1 à r0");

  /* Fin */
  arm_instruction(strcat(etiquette_fin, ":"), NULL, NULL, NULL, "etiquette fin");
  arm_instruction("push", "{r0}", NULL, NULL, "empile le resultat de la comparaison");
}

/* Instructions conditionelles */

void gen_tant_que(n_instr_cond *n)
{
  char *etiquette_debut = malloc_etiquette();
  char *declaration_debut = malloc_etiquette();
  char *etiquette_fin = malloc_etiquette();
  nouveau_nom_etiquette(etiquette_debut);
  nouveau_nom_etiquette(etiquette_fin);
  strcpy(declaration_debut, etiquette_debut);

  arm_instruction(strcat(declaration_debut, ":"), NULL, NULL, NULL, "etiquette debut");

  /* Analyse sémantique et évaluation de la condition */
  switch (n->exp->type_exp)
  {
  case i_operation:
    gen_exp(n->exp);
    break;

  case i_booleen:
    gen_exp(n->exp);
    break;

  default:
    fprintf(stderr, "Une instruction conditionelle doit utiliser une expression booléenne.\n");
    exit(1);
  }

  arm_instruction("pop", "{r0}", NULL, NULL, "dépile l'évaluation de l'expression dans r0");
  arm_instruction("cmp", "r0", "#0", NULL, "effectue l'opération de comparaison");

  arm_instruction("beq", etiquette_fin, NULL, NULL, "déplace le compteur de programme à l'etiquette fin");

  /* Boucle */
  arm_instruction("pop", "{r1}", NULL, NULL, "depile l'ancienne valeur de r1 dans r1");
  arm_instruction("pop", "{r0}", NULL, NULL, "depile l'ancienne valeur de r0 dans r0");

  gen_liste_instructions(n->instructions);

  arm_instruction("push", "{r0}", NULL, NULL, "empile r0"); // r0 et r1 sont les deux registres susceptibles d'être changés pendant l'évaluation de la condition
  arm_instruction("push", "{r1}", NULL, NULL, "empile r1");

  arm_instruction("beq", etiquette_debut, NULL, NULL, "déplace le compteur de programme à l'etiquette debut");

  /* Fin */
  arm_instruction(strcat(etiquette_fin, ":"), NULL, NULL, NULL, "etiquette fin");
}

void gen_si(n_instr_cond *n)
{
  /* Analyse sémantique */
  switch (n->exp->type_exp)
  {
  case i_operation:
    gen_exp(n->exp);
    break;

  case i_booleen:
    gen_exp(n->exp);
    break;

  default:
    fprintf(stderr, "Une instruction conditionelle doit utiliser une expression booléenne.\n");
    exit(1);
  }

  /* Génération de code */
  arm_instruction("pop", "{r0}", NULL, NULL, "dépile l'évaluation de l'expression dans r0");
  arm_instruction("cmp", "r0", "#0", NULL, "effectue l'opération de comparaison");

  char *etiquette_faux = malloc_etiquette();
  nouveau_nom_etiquette(etiquette_faux);

  arm_instruction("beq", etiquette_faux, NULL, NULL, "déplace le compteur de programme à la partie faux");
  gen_liste_instructions(n->instructions);

  /* Faux */
  arm_instruction(strcat(etiquette_faux, ":"), NULL, NULL, NULL, "etiquette faux");
}