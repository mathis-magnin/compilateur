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
	mov	r1, #7
	push	{r1}
	mov	r1, #45
	push	{r1}
	pop	{r1}		 @ dépile exp2 dans r1
	pop	{r0}		 @ dépile exp1 dans r0
	cmp	r0, r1		 @ effectue l'opération de comparaison
	ble	.e0		 @ déplace le compteur de programme à la partie vrai
	mov	r0, #0		 @ affecte 0 à r0
	b	.e1		 @ déplace le compteur de programme à la partie fin
	.e0:		 @ etiquette vrai
	mov	r0, #1		 @ affecte 1 à r0
	.e1:		 @ etiquette faux
	push	{r0}		 @ empile le résultat
	mov	r1, #48
	push	{r1}
	mov	r1, #47
	push	{r1}
	mov	r1, #1
	push	{r1}
	pop	{r1}		 @ dépile exp2 dans r1
	pop	{r0}		 @ dépile exp1 dans r0
	add	r0, r1, r0		 @ effectue l'opération r0+r1 et met le résultat dans r0
	push	{r0}		 @ empile le résultat
	pop	{r1}		 @ dépile exp2 dans r1
	pop	{r0}		 @ dépile exp1 dans r0
	cmp	r0, r1		 @ effectue l'opération de comparaison
	beq	.e2		 @ déplace le compteur de programme à la partie vrai
	mov	r0, #0		 @ affecte 0 à r0
	b	.e3		 @ déplace le compteur de programme à la partie fin
	.e2:		 @ etiquette vrai
	mov	r0, #1		 @ affecte 1 à r0
	.e3:		 @ etiquette faux
	push	{r0}		 @ empile le résultat
	pop	{r1}		 @ dépile exp2 dans r1
	pop	{r0}		 @ dépile exp1 dans r0
