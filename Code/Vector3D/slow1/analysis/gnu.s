	.file	"main.cpp"
	.text
	.p2align 4,,15
	.globl	_Z8subtractRKSt5arrayI8Vector3DLm256EES3_RS1_
	.type	_Z8subtractRKSt5arrayI8Vector3DLm256EES3_RS1_, @function
_Z8subtractRKSt5arrayI8Vector3DLm256EES3_RS1_:
.LFB2075:
	.cfi_startproc
	leaq	96(%rsi), %rcx
	leaq	96(%rdx), %rax
	cmpq	%rcx, %rdx
	setnb	%r8b
	cmpq	%rax, %rsi
	setnb	%cl
	orb	%cl, %r8b
	je	.L2
	leaq	96(%rdi), %rcx
	cmpq	%rcx, %rdx
	setnb	%cl
	cmpq	%rax, %rdi
	setnb	%al
	orb	%al, %cl
	je	.L2
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L4:
	vmovupd	32(%rdi,%rax), %ymm1
	vmovupd	64(%rdi,%rax), %ymm0
	vmovupd	(%rdi,%rax), %ymm2
	vsubpd	32(%rsi,%rax), %ymm1, %ymm1
	vsubpd	64(%rsi,%rax), %ymm0, %ymm0
	vsubpd	(%rsi,%rax), %ymm2, %ymm2
	vmovupd	%ymm1, 32(%rdx,%rax)
	vmovupd	%ymm2, (%rdx,%rax)
	vmovupd	%ymm0, 64(%rdx,%rax)
	addq	$96, %rax
	cmpq	$6144, %rax
	jne	.L4
	vzeroupper
	ret
	.p2align 4,,10
	.p2align 3
.L2:
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L5:
	vmovsd	8(%rdi,%rax), %xmm0
	vmovsd	(%rdi,%rax), %xmm2
	vsubsd	8(%rsi,%rax), %xmm0, %xmm1
	vsubsd	(%rsi,%rax), %xmm2, %xmm2
	vmovsd	16(%rdi,%rax), %xmm0
	vsubsd	16(%rsi,%rax), %xmm0, %xmm0
	vmovsd	%xmm2, (%rdx,%rax)
	vmovsd	%xmm1, 8(%rdx,%rax)
	vmovsd	%xmm0, 16(%rdx,%rax)
	addq	$24, %rax
	cmpq	$6144, %rax
	jne	.L5
	ret
	.cfi_endproc
.LFE2075:
	.size	_Z8subtractRKSt5arrayI8Vector3DLm256EES3_RS1_, .-_Z8subtractRKSt5arrayI8Vector3DLm256EES3_RS1_
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC2:
	.string	"Elapsed time: "
.LC3:
	.string	" ms "
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB2076:
	.cfi_startproc
	leaq	8(%rsp), %r10
	.cfi_def_cfa 10, 0
	andq	$-32, %rsp
	vxorpd	%xmm0, %xmm0, %xmm0
	xorl	%edx, %edx
	pushq	-8(%r10)
	vcvtsi2sd	%edi, %xmm0, %xmm0
	pushq	%rbp
	.cfi_escape 0x10,0x6,0x2,0x76,0
	movq	%rsp, %rbp
	pushq	%r12
	vaddsd	%xmm0, %xmm0, %xmm1
	.cfi_escape 0x10,0xc,0x2,0x76,0x78
	movl	%edi, %r12d
	pushq	%r10
	.cfi_escape 0xf,0x3,0x76,0x70,0x6
	leaq	-18480(%rbp), %rax
	pushq	%rbx
	subq	$18456, %rsp
	.cfi_escape 0x10,0x3,0x2,0x76,0x68
	vmulsd	.LC0(%rip), %xmm0, %xmm4
	vmulsd	.LC1(%rip), %xmm0, %xmm2
	vbroadcastsd	%xmm0, %ymm0
.L19:
	addq	$1, %rdx
	vmovapd	%ymm0, (%rax)
	addq	$96, %rax
	vmovapd	%ymm0, -64(%rax)
	vmovapd	%ymm0, -32(%rax)
	cmpq	$63, %rdx
	jbe	.L19
	vunpcklpd	%xmm2, %xmm4, %xmm3
	vunpcklpd	%xmm4, %xmm1, %xmm0
	vunpcklpd	%xmm1, %xmm2, %xmm2
	xorl	%edx, %edx
	vinsertf128	$0x1, %xmm3, %ymm2, %ymm5
	leaq	-12336(%rbp), %rax
	vinsertf128	$0x1, %xmm0, %ymm3, %ymm3
	vinsertf128	$0x1, %xmm2, %ymm0, %ymm0
.L20:
	addq	$1, %rdx
	vmovapd	%ymm0, (%rax)
	addq	$96, %rax
	vmovapd	%ymm3, -64(%rax)
	vmovapd	%ymm5, -32(%rax)
	cmpq	$63, %rdx
	jbe	.L20
	vzeroupper
	call	_ZNSt6chrono3_V212system_clock3nowEv
	movl	$10000000, %r11d
	xorl	%r10d, %r10d
	subl	%r12d, %r11d
	movq	%rax, %rbx
	testl	%r11d, %r11d
	jle	.L23
// setup base pointers into A,B,C
// note offsets 32 und 64 used for unrolling by factor of 3
	leaq	-18480(%rbp), %rax
	leaq	32(%rax), %r9
	leaq	-12336(%rbp), %rax
	leaq	32(%rax), %r8
	leaq	-18480(%rbp), %rax
	leaq	64(%rax), %rdi
	leaq	-12336(%rbp), %rax
	leaq	64(%rax), %rsi
	leaq	-6192(%rbp), %rax
	leaq	32(%rax), %rcx
	leaq	64(%rax), %rdx
	.p2align 4,,10
	.p2align 3

//
//      outer loop, n=0,1,2,...,10000000
//      counter: r10d (nLoop)
//      increment: 1
.L29:
//      reset inner loop counter to zero (n)
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L22:
//
//      inner loop, i=0,96,192,..,768
//      counter: rax
//      increment: 96 bytes / 12 doubles
//      (unrolled by factor of 3)
//
//      load A offset 32
	vmovapd	(%r9,%rax), %ymm1
//      load A offset 64
	vmovapd	(%rdi,%rax), %ymm0
//      subtract B offset 32
	vsubpd	(%r8,%rax), %ymm1, %ymm1
//      subtract B offset 64
	vsubpd	(%rsi,%rax), %ymm0, %ymm0
//      load A offset 0
	vmovapd	-18480(%rbp,%rax), %ymm2
//      subtract B offset 0
	vsubpd	-12336(%rbp,%rax), %ymm2, %ymm2
//store C for offsets 0,32,64
	vmovapd	%ymm2, -6192(%rbp,%rax)
	vmovapd	%ymm1, (%rcx,%rax)
	vmovapd	%ymm0, (%rdx,%rax)
        // increase by loop counter by 12 doubles
	addq	$96, %rax
        // loop size is 768 doubles
	cmpq	$6144, %rax
// end inner
	jne	.L22
	addl	$1, %r10d
	cmpl	%r10d, %r11d
// end outer
	jne	.L29



	vzeroupper
.L23:
	call	_ZNSt6chrono3_V212system_clock3nowEv
	movl	$.LC2, %esi
	movl	$_ZSt4cout, %edi
	movabsq	$4835703278458516699, %rdx
	subq	%rbx, %rax
	movq	%rax, %rcx
	imulq	%rdx
	sarq	$63, %rcx
	sarq	$18, %rdx
	movq	%rdx, %rbx
	movl	$14, %edx
	subq	%rcx, %rbx
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movl	%ebx, %esi
	movl	$_ZSt4cout, %edi
	call	_ZNSolsEi
	movl	$4, %edx
	movl	$.LC3, %esi
	movq	%rax, %rbx
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movq	%rbx, %rdi
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	vmovsd	-6192(%rbp), %xmm0
	movl	$_ZSt4cout, %edi
	call	_ZNSo9_M_insertIdEERSoT_
	movq	%rax, %rdi
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	addq	$18456, %rsp
	xorl	%eax, %eax
	popq	%rbx
	popq	%r10
	.cfi_def_cfa 10, 0
	popq	%r12
	popq	%rbp
	leaq	-8(%r10), %rsp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2076:
	.size	main, .-main
	.p2align 4,,15
	.type	_GLOBAL__sub_I__Z8subtractRKSt5arrayI8Vector3DLm256EES3_RS1_, @function
_GLOBAL__sub_I__Z8subtractRKSt5arrayI8Vector3DLm256EES3_RS1_:
.LFB2557:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	$_ZStL8__ioinit, %edi
	call	_ZNSt8ios_base4InitC1Ev
	movl	$__dso_handle, %edx
	movl	$_ZStL8__ioinit, %esi
	movl	$_ZNSt8ios_base4InitD1Ev, %edi
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	jmp	__cxa_atexit
	.cfi_endproc
.LFE2557:
	.size	_GLOBAL__sub_I__Z8subtractRKSt5arrayI8Vector3DLm256EES3_RS1_, .-_GLOBAL__sub_I__Z8subtractRKSt5arrayI8Vector3DLm256EES3_RS1_
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__Z8subtractRKSt5arrayI8Vector3DLm256EES3_RS1_
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC0:
	.long	0
	.long	1074266112
	.align 8
.LC1:
	.long	0
	.long	1074790400
	.hidden	__dso_handle
	.ident	"GCC: (GNU) 6.2.0 20160822 (Cray Inc.)"
	.section	.note.GNU-stack,"",@progbits
