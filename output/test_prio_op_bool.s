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
	mov	r1, #0
	push	{r1}
	mov	r1, #1
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
	pop	{r1}		 @ dépile exp2 dans r1
	pop	{r0}		 @ dépile exp1 dans r0
	mul	r0, r0, r1		 @ effectue l'opération r0*r1
	push	{r0}		 @ empile le résultat
	mov	r1, #1
	push	{r1}
	pop	{r1}		 @ dépile exp2 dans r1
	pop	{r0}		 @ dépile exp1 dans r0
	mul	r0, r0, r1		 @ effectue l'opération r0*r1
	push	{r0}		 @ empile le résultat
	pop	{r1}
	ldr	r0, =.LC1
	bl	printf
	mov	r0, #0
	pop	{fp, pc}
