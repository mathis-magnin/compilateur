.LC0:
	.ascii	"%d\000"
	.align	2
.LC1:
	.ascii	"%d\012\000"
	.text
	.align	2
	.global	main
main:
	push	{fp,lr}
	add	fp, sp, #4
	mov	r1, #4
	push	{r1}
	mov	r1, #5
	push	{r1}
	pop	{r1}		 @ dépile exp2 dans r1
	pop	{r0}		 @ dépile exp1 dans r0
	cmp	r0, r1		 @ effectue l'opération de comparaison
	blt	.e0		 @ déplace le compteur de programme à la partie vrai
	mov	r0, #0		 @ affecte 0 à r0
	b	.e1		 @ déplace le compteur de programme à la partie fin
	.e0:		 @ etiquette vrai
	mov	r0, #1		 @ affecte 1 à r0
	.e1:		 @ etiquette fin
	push	{r0}		 @ empile le resultat de la comparaison
	mov	r1, #12
	push	{r1}
	mov	r1, #42
	push	{r1}
	pop	{r1}		 @ dépile exp2 dans r1
	pop	{r0}		 @ dépile exp1 dans r0
	cmp	r0, r1		 @ effectue l'opération de comparaison
	blt	.e2		 @ déplace le compteur de programme à la partie vrai
	mov	r0, #0		 @ affecte 0 à r0
	b	.e3		 @ déplace le compteur de programme à la partie fin
	.e2:		 @ etiquette vrai
	mov	r0, #1		 @ affecte 1 à r0
	.e3:		 @ etiquette fin
	push	{r0}		 @ empile le resultat de la comparaison
	pop	{r1}		 @ dépile exp2 dans r1
	pop	{r0}		 @ dépile exp1 dans r0
	mul	r0, r0, r1		 @ effectue l'opération r0*r1
	push	{r0}		 @ empile le résultat
	mov	r1, #0
	push	{r1}
	pop	{r1}		 @ dépile exp2 dans r1
	pop	{r0}		 @ dépile exp1 dans r0
	add	r0, r0, r1		 @ effectue l'opération r0+r1
	push	{r0}		 @ empile le résultat
	pop	{r0}		 @ dépile dans r0
	cmp	r0, #1		 @ compare r0 à 1 (r0-1)
	push	{r0}		 @ empile le résultat
	pop	{r0}		 @ dépile dans r0
	movlt	r0, #0		 @ si le résultat est strictement négatif, affecte 0 à r0
	movge	r0, #1		 @ sinon, affecte 1 à r0
	push	{r0}		 @ empile le résultat
	pop	{r0}		 @ dépile l'évaluation de l'expression dans r0
	cmp	r0, #0		 @ effectue l'opération de comparaison
	beq	.e8		 @ déplace le compteur de programme à la partie faux
	mov	r1, #1
	push	{r1}
	pop	{r1}
	ldr	r0, =.LC1
	bl	printf
	mov	r1, #12
	push	{r1}
	mov	r1, #3
	push	{r1}
	pop	{r1}		 @ dépile exp2 dans r1
	pop	{r0}		 @ dépile exp1 dans r0
	cmp	r0, r1		 @ effectue l'opération de comparaison
	blt	.e9		 @ déplace le compteur de programme à la partie vrai
	mov	r0, #0		 @ affecte 0 à r0
	b	.e10		 @ déplace le compteur de programme à la partie fin
	.e9:		 @ etiquette vrai
	mov	r0, #1		 @ affecte 1 à r0
	.e10:		 @ etiquette fin
	push	{r0}		 @ empile le resultat de la comparaison
	pop	{r0}		 @ dépile l'évaluation de l'expression dans r0
	cmp	r0, #0		 @ effectue l'opération de comparaison
	beq	.e11		 @ déplace le compteur de programme à la partie faux
	mov	r1, #2
	push	{r1}
	pop	{r1}
	ldr	r0, =.LC1
	bl	printf
	.e11:		 @ etiquette faux
	.e8:		 @ etiquette faux
	mov	r1, #1
	push	{r1}
	pop	{r0}		 @ dépile l'évaluation de l'expression dans r0
	cmp	r0, #0		 @ effectue l'opération de comparaison
	beq	.e12		 @ déplace le compteur de programme à la partie faux
	mov	r1, #3
	push	{r1}
	pop	{r1}
	ldr	r0, =.LC1
	bl	printf
	.e12:		 @ etiquette faux
	mov	r1, #0
	push	{r1}
	pop	{r0}		 @ dépile l'évaluation de l'expression dans r0
	cmp	r0, #0		 @ effectue l'opération de comparaison
	beq	.e13		 @ déplace le compteur de programme à la partie faux
	mov	r1, #4
	push	{r1}
	pop	{r1}
	ldr	r0, =.LC1
	bl	printf
	mov	r1, #5
	push	{r1}
	pop	{r1}
	ldr	r0, =.LC1
	bl	printf
	.e13:		 @ etiquette faux
	mov	r0, #0
	pop	{fp, pc}
