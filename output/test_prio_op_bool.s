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
	mov	r1, #0
	push	{r1}
	pop	{r1}		 @ dépile exp2 dans r1
	pop	{r0}		 @ dépile exp1 dans r0
	mul	r0, r0, r1		 @ effectue l'opération r0*r1
	push	{r0}		 @ empile le résultat
	mov	r0, #0		 @ affecte 0 à r0
	b	.e1		 @ déplace le compteur de programme à la partie fin
	.e0:		 @ etiquette vrai
	mov	r0, #1		 @ affecte 1 à r0
	.e1:		 @ etiquette faux
	mov	r1, #0
	push	{r1}
	mov	r1, #1
	push	{r1}
	pop	{r1}		 @ dépile exp2 dans r1
	pop	{r0}		 @ dépile exp1 dans r0
	add	r2, r0, r1		 @ effectue l'opération r0+r1
	cmp	r2, r2, #1		 @ compare r2 à 1 (r2-1)
	blt	.e3		 @ déplace le compteur de programme à la partie fin
	bge	.e2		 @ déplace la compteur de programme à la partie vraie
	mov	r0, #0		 @ affecte 0 à r0
	b	.e3		 @ déplace le compteur de programme à la partie fin
	.e2:		 @ etiquette vrai
	mov	r0, #1		 @ affecte 1 à r0
	.e3:		 @ etiquette faux
	pop	{r1}		 @ dépile exp2 dans r1
	pop	{r0}		 @ dépile exp1 dans r0
	mul	r0, r0, r1		 @ effectue l'opération r0*r1
	push	{r0}		 @ empile le résultat
	mov	r0, #0		 @ affecte 0 à r0
	b	.e5		 @ déplace le compteur de programme à la partie fin
	.e4:		 @ etiquette vrai
	mov	r0, #1		 @ affecte 1 à r0
	.e5:		 @ etiquette faux
	mov	r1, #1
	push	{r1}
	pop	{r1}		 @ dépile exp2 dans r1
	pop	{r0}		 @ dépile exp1 dans r0
	mul	r0, r0, r1		 @ effectue l'opération r0*r1
	push	{r0}		 @ empile le résultat
	mov	r0, #0		 @ affecte 0 à r0
	b	.e7		 @ déplace le compteur de programme à la partie fin
	.e6:		 @ etiquette vrai
	mov	r0, #1		 @ affecte 1 à r0
	.e7:		 @ etiquette faux
	pop	{r1}
	ldr	r0, =.LC1
	bl	printf
	mov	r0, #0
	pop	{fp, pc}
