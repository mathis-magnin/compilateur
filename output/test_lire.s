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
	ldr	r0, =.LC1
	sub	sp, sp, #4		 @ effectue l'opération sp-4 et stocke le résultat dans sp
	mov	r1, sp
	bl	scanf
	pop	{r1}		 @ dépilé dans r1
	push	{r1}
	pop	{r1}
	ldr	r0, =.LC1
	bl	printf
	mov	r0, #0
	pop	{fp, pc}
