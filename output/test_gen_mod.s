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
	mov	r1, #2
	push	{r1}
	pop	{r1}		 @ dépile exp2 dans r1
	pop	{r0}		 @ dépile exp1 dans r0
	bl 	__aeabi_idivmod		 @ 
	push	{r1}		 @ empile le résultat
	pop	{r1}
	ldr	r0, =.LC1
	bl	printf
	mov	r0, #0
	pop	{fp, pc}
