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

void gen_prog(n_programme *n)
{

  // Déclaration de __aeabi_idiv
  asm(".global __aeabi_idiv");
  // Déclaration de __aeabi_idivmod
  asm(".global __aeabi_idivmod");

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
  if (n->type_instruction == i_ecrire)
  {
    gen_exp(n->u.exp);                                // on calcule et empile la valeur de l'expression
    arm_instruction("pop", "{r1}", NULL, NULL, NULL); // on dépile la valeur d'expression sur r1
    arm_instruction("ldr", "r0", "=.LC1", NULL, NULL);
    arm_instruction("bl", "printf", NULL, NULL, NULL); // on envoie la valeur de r1 sur la sortie standard
  }
  /* instruction lire non implémentée syntaxiquement
  else if (n->type_instruction == i_lire)
  {
    arm_instruction("ldr", "r0", "=.LC1", NULL, NULL);
    arm_instruction("sub", "sp", "sp", "#4", "effectue l'opération sp-4 et stocke le résultat dans sp");
    arm_instruction("mov", "r1", "sp", NULL, NULL);   // Copie l'adresse de sp dans r1
    arm_instruction("bl", "scanf", NULL, NULL, NULL); // on récupère les infos de l'entrée standard
  }*/
  else
  {
    fprintf(stderr, "génération type instruction non implémenté\n");
    exit(1);
  }
}

void gen_exp(n_exp *n)
{
  if (n->type_exp == i_operation)
  {
    gen_operation(n->u.operation);
  }
  else if (n->type_exp == i_entier)
  {
    char buffer[12];
    sprintf(buffer, "#%d", n->u.valeur);
    arm_instruction("mov", "r1", buffer, NULL, NULL);  // on met sur la pile la valeur entière
    arm_instruction("push", "{r1}", NULL, NULL, NULL); // on met sur la pile la valeur entière
  }
  else if (n->type_exp == i_booleen)
  {
    char buffer[12];
    sprintf(buffer, "#%d", n->u.valeur);
    arm_instruction("mov", "r1", buffer, NULL, NULL);  // on met sur la pile la valeur booléenne (0 ou 1)
    arm_instruction("push", "{r1}", NULL, NULL, NULL); // on met sur la pile la valeur booléenne (0 ou 1)
  }
  else
  {
    fprintf(stderr, "génération type expression non implémenté\n");
    exit(1);
  }
}

void gen_operation(n_operation *n)
{
  /* Vérification de type non fonctionnelle */
  printf("type d'opération : %c\n", n->type_operation);
  switch (n->type_operation)
  {
  case '+':
  case '-':
  case '*':
  case '/':
  case '%':
    if (n->exp1->type_exp != i_operation && n->exp2->type_exp != i_operation)
    {
      if (n->exp1->type_exp != i_entier || n->exp2->type_exp != i_entier)
      {
        printf("Premier morceau de l'expression : %c\n", n->exp1->u.operation->type_operation);
        printf("Second morceau de l'expression : %d\n", n->exp2->u.valeur);
        fprintf(stderr, "Erreur de typage, un booléen ou plus pour une opération entière");
        return;
      }
    }
    break;
  case 'e':
  case 'd':
    if (n->exp1->type_exp != i_operation && n->exp2->type_exp != i_operation)
    {
      if (n->exp1->type_exp != n->exp2->type_exp)
      {
        printf("Premier morceau de l'expression : %c\n", n->exp1->u.operation->type_operation);
        printf("Second morceau de l'expression : %d\n", n->exp2->u.valeur);
        fprintf(stderr, "Erreur de typage, comparaison entre deux éléments de type différents");
        return;
      }
    }
    break;
  case '<':
  case '>':
  case 'i':
  case 's':
    if (n->exp1->type_exp != i_operation && n->exp2->type_exp != i_operation)
    {
      if (n->exp1->type_exp != i_entier || n->exp2->type_exp != i_entier)
      {
        fprintf(stderr, "Erreur de typage, comparaison d'ordre entre deux éléments de type différents");
        return;
      }
    }
    break;
  case '|':
  case '&':
  case '!':
    if (n->exp1->type_exp != i_operation && n->exp2->type_exp != i_operation)
    {
      if (n->exp1->type_exp != i_booleen || n->exp2->type_exp != i_booleen)
      {
        fprintf(stderr, "Erreur de typage, un entier ou plus pour une opération booléenne");
        return;
      }
    }
    break;
  }
  gen_exp(n->exp1); // on calcule et empile la valeur de exp1
  gen_exp(n->exp2); // on calcule et empile la valeur de exp2
  arm_instruction("pop", "{r1}", NULL, NULL, "dépile exp2 dans r1");
  arm_instruction("pop", "{r0}", NULL, NULL, "dépile exp1 dans r0");
  if (n->type_operation == '+')
  {
    arm_instruction("add", "r0", "r1", "r0", "effectue l'opération r0+r1 et met le résultat dans r0");
  }
  else if (n->type_operation == '-')
  {
    arm_instruction("sub", "r0", "r0", "r1", "effectue l'opération r0-r1 et met le résultat dans r0");
  }
  else if (n->type_operation == '*')
  {
    arm_instruction("mul", "r0", "r1", "r0", "effectue l'opération r0*r1 et met le résultat dans r0");
  }
  else if (n->type_operation == '/')
  {
    arm_instruction("bl ", "__aeabi_idiv", "", "", "");
  }
  else if (n->type_operation == '%')
  {
    arm_instruction("bl ", "__aeabi_idivmod", "", "", "");
  }
  else if (n->type_operation == '|')
  {
    arm_instruction("add", "r2", "r0", "r1", "effectue l'opération r0+r1 et met le résultat dans r2");
    arm_instruction("cmp", "r2", "r2", "#0", "compare r2 à 0 (r2-0) et met le résultat dans r2");
  }
  else if (n->type_operation == '&')
  {
    arm_instruction("mul", "r0", "r0", "r1", "effectue l'opération (r0 et r1) et met le résultat dans r0");
  }
  else if (n->type_operation == '!')
  {
    printf("exp1 == %d\n", n->exp1->u.valeur);
    printf("exp2 == %d\n", n->exp2->u.valeur);
    arm_instruction("add", "r0", "r0", "#1", "effectue l'opération r0+1 et met le résultat dans r0");
    // Charger r0
    char buffer[12];
    sprintf(buffer, "#%d", n->exp1->u.valeur);
    arm_instruction("mov", "r0", buffer, NULL, NULL);
    arm_instruction("push", "{r0}", NULL, NULL, NULL);
    // Charger l'immédiat 2
    char buffer2[12];
    sprintf(buffer2, "#%d", 2);
    arm_instruction("mov", "#2", buffer2, NULL, NULL);
    arm_instruction("push", "{r1}", NULL, NULL, NULL);
    // Appeler la fonction de modulo
    arm_instruction("bl ", "__aeabi_idivmod", "", "", "");
    // Le résultat est chargé dans r1
  }
  else
  {
    fprintf(stderr, "génération opération %d non implémenté\n", n->type_operation);
    exit(1);
  }
  arm_instruction("push", "{r0}", NULL, NULL, "empile le résultat");
}
