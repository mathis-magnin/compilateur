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
	mov	r1, #0
	push	{r1}
	pop	{r0}		 @ dépile l'évaluation de l'expression dans r0
	cmp	r0, #0		 @ effectue l'opération de comparaison
	beq	.e0		 @ déplace le compteur de programme à la partie faux
	mov	r1, #0
	push	{r1}
	pop	{r1}
	ldr	r0, =.LC1
	bl	printf
	.e0:		 @ etiquette vrai
	mov	r1, #0
	push	{r1}
	pop	{r0}		 @ dépile l'évaluation de l'expression dans r0
	cmp	r0, #0		 @ effectue l'opération de comparaison
	beq	.e1		 @ déplace le compteur de programme à la partie faux
	mov	r1, #0
	push	{r1}
	pop	{r1}
	ldr	r0, =.LC1
	bl	printf
	.e1:		 @ etiquette vrai
	mov	r1, #0
	push	{r1}
	pop	{r0}		 @ dépile l'évaluation de l'expression dans r0
	cmp	r0, #0		 @ effectue l'opération de comparaison
	beq	.e2		 @ déplace le compteur de programme à la partie faux
	mov	r1, #0
	push	{r1}
	pop	{r1}
	ldr	r0, =.LC1
	bl	printf
	.e2:		 @ etiquette vrai
	mov	r1, #1
	push	{r1}
	pop	{r0}		 @ dépile l'évaluation de l'expression dans r0
	cmp	r0, #0		 @ effectue l'opération de comparaison
	beq	.e3		 @ déplace le compteur de programme à la partie faux
	mov	r1, #4
	push	{r1}
	pop	{r1}
	ldr	r0, =.LC1
	bl	printf
	.e3:		 @ etiquette vrai
	mov	r1, #1
	push	{r1}
	pop	{r0}		 @ dépile l'évaluation de l'expression dans r0
	cmp	r0, #0		 @ effectue l'opération de comparaison
	beq	.e4		 @ déplace le compteur de programme à la partie faux
	mov	r1, #5
	push	{r1}
	pop	{r1}
	ldr	r0, =.LC1
	bl	printf
	.e4:		 @ etiquette vrai
	mov	r1, #0
	push	{r1}
	pop	{r0}		 @ dépile l'évaluation de l'expression dans r0
	cmp	r0, #0		 @ effectue l'opération de comparaison
	beq	.e5		 @ déplace le compteur de programme à la partie faux
	mov	r1, #0
	push	{r1}
	pop	{r1}
	ldr	r0, =.LC1
	bl	printf
	.e5:		 @ etiquette vrai
	mov	r1, #1
	push	{r1}
	pop	{r0}		 @ dépile l'évaluation de l'expression dans r0
	cmp	r0, #0		 @ effectue l'opération de comparaison
	beq	.e6		 @ déplace le compteur de programme à la partie faux
	mov	r1, #6
	push	{r1}
	pop	{r1}
	ldr	r0, =.LC1
	bl	printf
	.e6:		 @ etiquette vrai
	mov	r1, #1
	push	{r1}
	pop	{r0}		 @ dépile l'évaluation de l'expression dans r0
	cmp	r0, #0		 @ effectue l'opération de comparaison
	beq	.e7		 @ déplace le compteur de programme à la partie faux
	mov	r1, #0
	push	{r1}
	pop	{r1}
	ldr	r0, =.LC1
	bl	printf
	.e7:		 @ etiquette vrai
	mov	r0, #0
	pop	{fp, pc}
