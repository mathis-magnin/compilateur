INPUT := $(basename $(notdir $(wildcard input/*.flo)))
OUTPUT_DIR := output

flo_vers_exercutable: main
	for a in $(INPUT); do \
		echo "compilation: $$a"; \
		if ./main -g input/$$a.flo > $(OUTPUT_DIR)/$$a.s; \
		then \
		arm-linux-gnueabi-gcc $(OUTPUT_DIR)/$$a.s -static -o $(OUTPUT_DIR)/$$a; \
		fi; \
	done;

main: analyse_lexicale analyse_syntaxique
	gcc -Wall main.c analyse_lexicale.c analyse_syntaxique.c arbre_abstrait.c generation_code.c -o main

analyse_syntaxique :
	bison analyse_syntaxique.y --defines=symboles.h -o analyse_syntaxique.c

analyse_lexicale:
	flex -o analyse_lexicale.c analyse_lexicale.l
