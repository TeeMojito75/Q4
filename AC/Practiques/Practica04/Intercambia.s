 .text
	.align 4
	.globl Intercambiar
	.type Intercambiar,@function
Intercambiar:# Aqui viene vuestro codigo
	pushl %ebp
	movl %esp, %ebp
	subl $12, %esp

	movl 12(%ebp), %eax # i 
	imul $12, %eax, %eax
	addl 8(%ebp), %eax  #eax <- v[i]

	movl 16(%ebp), %ecx # j 
	imul $12, %ecx, %ecx
	addl 8(%ebp), %ecx  #eax <- v[j]
	
	# canvi entre v[i].c i v[j].c
	movb (%eax), %dl
	movb %dl, -4(%ebp) # s = v[i].c
	movb (%ecx), %dl
	movb %dl, (%eax)
	movb -4(%ebp), %dl
	movb %dl, (%ecx)

	movl 4(%eax), %edx
	movl %edx, -12(%ebp) # tmp = v[i].k
	movl 4(%ecx), %edx
	movl %edx, 4(%eax)
	movl -12(%ebp), %edx
	movl %edx, 4(%ecx)

	movl 8(%eax), %edx
	movl %edx, -8(%ebp) # aux = v[i].m
	movl 8(%ecx), %edx
	movl %edx, 8(%eax)
	movl -8(%ebp), %edx
	movl %edx, 8(%ecx)

	movl %ebp, %esp
	popl %ebp
	ret
