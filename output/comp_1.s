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
	mov	r1, #1
	push	{r1}
	mov	r1, #2
	push	{r1}
	pop	{r1}		 @ dépile exp2 dans r1
	pop	{r0}		 @ dépile exp1 dans r0
	cmp	r0, r1		 @ effectue l'opération de comparaison
	blt	.e0		 @ déplace le compteur de programme à la partie vrai
	mov	r0, #0		 @ affecte 0 à r0
	b	.e1		 @ déplace le compteur de programme à la partie fin
	.e0:		 @ etiquette vrai
	mov	r0, #1		 @ affecte 1 à r0
	.e1:		 @ etiquette faux
	push	{r0}		 @ empile le résultat
	pop	{r1}
	ldr	r0, =.LC1
	bl	printf
	mov	r1, #2
	push	{r1}
	mov	r1, #2
	push	{r1}
	pop	{r1}		 @ dépile exp2 dans r1
	pop	{r0}		 @ dépile exp1 dans r0
	cmp	r0, r1		 @ effectue l'opération de comparaison
	blt	.e2		 @ déplace le compteur de programme à la partie vrai
	mov	r0, #0		 @ affecte 0 à r0
	b	.e3		 @ déplace le compteur de programme à la partie fin
	.e2:		 @ etiquette vrai
	mov	r0, #1		 @ affecte 1 à r0
	.e3:		 @ etiquette faux
	push	{r0}		 @ empile le résultat
	pop	{r1}
	ldr	r0, =.LC1
	bl	printf
	mov	r1, #3
	push	{r1}
	mov	r1, #2
	push	{r1}
	pop	{r1}		 @ dépile exp2 dans r1
	pop	{r0}		 @ dépile exp1 dans r0
	cmp	r0, r1		 @ effectue l'opération de comparaison
	blt	.e4		 @ déplace le compteur de programme à la partie vrai
	mov	r0, #0		 @ affecte 0 à r0
	b	.e5		 @ déplace le compteur de programme à la partie fin
	.e4:		 @ etiquette vrai
	mov	r0, #1		 @ affecte 1 à r0
	.e5:		 @ etiquette faux
	push	{r0}		 @ empile le résultat
	pop	{r1}
	ldr	r0, =.LC1
	bl	printf
	mov	r1, #1
	push	{r1}
	mov	r1, #2
	push	{r1}
	pop	{r1}		 @ dépile exp2 dans r1
	pop	{r0}		 @ dépile exp1 dans r0
	cmp	r0, r1		 @ effectue l'opération de comparaison
	ble	.e6		 @ déplace le compteur de programme à la partie vrai
	mov	r0, #0		 @ affecte 0 à r0
	b	.e7		 @ déplace le compteur de programme à la partie fin
	.e6:		 @ etiquette vrai
	mov	r0, #1		 @ affecte 1 à r0
	.e7:		 @ etiquette faux
	push	{r0}		 @ empile le résultat
	pop	{r1}
	ldr	r0, =.LC1
	bl	printf
	mov	r1, #2
	push	{r1}
	mov	r1, #2
	push	{r1}
	pop	{r1}		 @ dépile exp2 dans r1
	pop	{r0}		 @ dépile exp1 dans r0
	cmp	r0, r1		 @ effectue l'opération de comparaison
	ble	.e8		 @ déplace le compteur de programme à la partie vrai
	mov	r0, #0		 @ affecte 0 à r0
	b	.e9		 @ déplace le compteur de programme à la partie fin
	.e8:		 @ etiquette vrai
	mov	r0, #1		 @ affecte 1 à r0
	.e9:		 @ etiquette faux
	push	{r0}		 @ empile le résultat
	pop	{r1}
	ldr	r0, =.LC1
	bl	printf
	mov	r1, #3
	push	{r1}
	mov	r1, #2
	push	{r1}
	pop	{r1}		 @ dépile exp2 dans r1
	pop	{r0}		 @ dépile exp1 dans r0
	cmp	r0, r1		 @ effectue l'opération de comparaison
	ble	.e10		 @ déplace le compteur de programme à la partie vrai
	mov	r0, #0		 @ affecte 0 à r0
	b	.e11		 @ déplace le compteur de programme à la partie fin
	.e10:		 @ etiquette vrai
	mov	r0, #1		 @ affecte 1 à r0
	.e11:		 @ etiquette faux
	push	{r0}		 @ empile le résultat
	pop	{r1}
	ldr	r0, =.LC1
	bl	printf
	mov	r0, #0
	pop	{fp, pc}