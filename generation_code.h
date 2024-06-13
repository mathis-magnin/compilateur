#ifndef __GENERATION_CODE__
#define __GENERATION_CODE__

void gen_prog(n_programme *n);
void gen_liste_instructions(n_l_instructions *n);
void gen_instruction(n_instruction *n);
void gen_exp(n_exp *n);
void gen_operation(n_operation *n);
void gen_operation_entiere(n_operation *n);
void gen_comparaison(n_operation *n);
void gen_si(n_instr_cond *n);
void gen_tant_que(n_instr_cond *n);

#endif
