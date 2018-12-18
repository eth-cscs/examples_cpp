	.text
	.ident	"Cray C++ : Version 8.7.3"
	.file	"The Cpu Module"
                                        # Start of file scope inline assembly
	.pushsection	.note.ftn_module_data
	.balign	4
	.4byte	10, 1f-0f, 8
	.asciz	"Cray Inc."
	.balign	4
0:
	.ascii	"\076\370\030\134\277\030\000\000\001\000\001\000\023\000"
	.ascii	"\000\000\006\000\000\000\057\164\155\160\057\160\145\137"
	.ascii	"\066\063\063\065\057\057\160\154\144\151\162\000\155\141"
	.ascii	"\151\156\056\163\000"
	.balign	4
1:	.popsection

                                        # End of file scope inline assembly
	.globl	_Z8subtractRKSt5arrayI8Vector3DLm256EES3_RS1_
	.p2align	5, 0x90
	.type	_Z8subtractRKSt5arrayI8Vector3DLm256EES3_RS1_,@function
_Z8subtractRKSt5arrayI8Vector3DLm256EES3_RS1_: # @_Z8subtractRKSt5arrayI8Vector3DLm256EES3_RS1_
	.cfi_startproc
..TxtBeg_F1:
	.file	1  "main.cpp"
	.loc	1  37  0
# BB#0:                                 # %", bb1"
	xorl	%r9d, %r9d
	xorl	%r8d, %r8d
	.p2align	5, 0x90
.LBB_Z8subtractRKSt5arrayI8Vector3DLm256EES3_RS1__1: # %"@cfe_1371$_Z8subtractRKSt5arrayI8Vector3DLm256EES3_RS1_"
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_2 Depth 2
	.loc	1  41  0
	vmovsd	(%rdi,%r9,8), %xmm0     # main.cpp:41
                                        # xmm0 = mem[0],zero
	vsubsd	(%rsi,%r9,8), %xmm0, %xmm0 # main.cpp:41
	vmovsd	%xmm0, -24(%rsp)        # main.cpp:41
	vmovsd	8(%rdi,%r9,8), %xmm0    # main.cpp:41
                                        # xmm0 = mem[0],zero
	vsubsd	8(%rsi,%r9,8), %xmm0, %xmm0 # main.cpp:41
	vmovsd	%xmm0, -16(%rsp)        # main.cpp:41
	vmovsd	16(%rdi,%r9,8), %xmm0   # main.cpp:41
                                        # xmm0 = mem[0],zero
	vsubsd	16(%rsi,%r9,8), %xmm0, %xmm0 # main.cpp:41
	leaq	(%rdx,%r9,8), %r10      # main.cpp:41
	vmovsd	%xmm0, -8(%rsp)         # main.cpp:41
	xorl	%eax, %eax
	.p2align	5, 0x90
.LBB_Z8subtractRKSt5arrayI8Vector3DLm256EES3_RS1__2: # %"file main.cpp, line 41, in inner loop at depth 1, bb1878"
                                        #   Parent Loop BB0_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	-24(%rsp,%rax,8), %rcx  # main.cpp:41
	movq	%rcx, (%r10,%rax,8)     # main.cpp:41
	incq	%rax                    # main.cpp:41
	cmpq	$3, %rax                # main.cpp:41
	jl	.LBB_Z8subtractRKSt5arrayI8Vector3DLm256EES3_RS1__2 # main.cpp:41
# BB#3:                                 # %"file main.cpp, line 41, in loop at depth 0, bb11"
                                        #   in Loop: Header=BB0_1 Depth=1
	addq	$3, %r9                 # main.cpp:41
	.loc	1  40  0
	incq	%r8                     # main.cpp:40
	cmpq	$256, %r8               # main.cpp:40
                                        # imm = 0x100
	jl	.LBB_Z8subtractRKSt5arrayI8Vector3DLm256EES3_RS1__1 # main.cpp:40
# BB#4:                                 # %"@cfe_1372$_Z8subtractRKSt5arrayI8Vector3DLm256EES3_RS1_"
	.loc	1  42  0
	retq                            # main.cpp:42
..TxtEnd_F1:
.Lfunc_end0:
	.size	_Z8subtractRKSt5arrayI8Vector3DLm256EES3_RS1_, .Lfunc_end0-_Z8subtractRKSt5arrayI8Vector3DLm256EES3_RS1_
	.cfi_endproc

	.section	.rodata.cst8,"aM",@progbits,8
	.p2align	3
.LCPI1_0:
	.quad	4613937818241073152     # double 3
.LCPI1_1:
	.quad	4616189618054758400     # double 4
	.text
	.globl	main
	.p2align	5, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
..TxtBeg_F2:
	.loc	1  44  0
# BB#0:                                 # %", bb1"
	pushq	%rbp
.Lcfi0:
	.cfi_def_cfa_offset 16
.Lcfi1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Lcfi2:
	.cfi_def_cfa_register %rbp
	.loc	1  48  0
	pushq	%rbx                    # main.cpp:48
	andq	$-32, %rsp
	subq	$18624, %rsp            # main.cpp:48
                                        # imm = 0x48C0
.Lcfi3:
	.cfi_offset %rbx, -24
	vcvtsi2sdl	%edi, %xmm0, %xmm0 # main.cpp:48
	vmovsd	%xmm0, (%rsp)           # main.cpp:48
	vmovsd	%xmm0, 8(%rsp)          # main.cpp:48
	vmovsd	%xmm0, 16(%rsp)         # main.cpp:48
	.loc	1  49  0
	vaddsd	%xmm0, %xmm0, %xmm1     # main.cpp:49
	.loc	1  48  0
	movq	16(%rsp), %rax          # main.cpp:48
	vmovaps	(%rsp), %xmm2           # main.cpp:48
	movq	%rax, 80(%rsp)          # main.cpp:48
	vmovaps	%xmm2, 64(%rsp)         # main.cpp:48
	.loc	1  49  0
	vmovsd	%xmm1, 32(%rsp)         # main.cpp:49
	vmulsd	.LCPI1_0(%rip), %xmm0, %xmm1 # main.cpp:49
	vmovsd	%xmm1, 40(%rsp)         # main.cpp:49
	vmulsd	.LCPI1_1(%rip), %xmm0, %xmm0 # main.cpp:49
	vmovsd	%xmm0, 48(%rsp)         # main.cpp:49
	movq	48(%rsp), %rax          # main.cpp:49
	vmovaps	32(%rsp), %xmm0         # main.cpp:49
	movq	%rax, 112(%rsp)         # main.cpp:49
	vmovaps	%xmm0, 96(%rsp)         # main.cpp:49
	movq	%rsp, %rax
	addq	$128, %rax
	movq	%rax, %rcx
	.p2align	5, 0x90
.LBBmain_1:                             # %"file main.cpp, line 53, in inner loop at depth 0, bb8184"
                                        # =>This Inner Loop Header: Depth=1
	.loc	1  53  0
	movq	80(%rsp), %rdx          # main.cpp:53
	movq	%rdx, 16(%rcx)          # main.cpp:53
	vmovaps	64(%rsp), %xmm0         # main.cpp:53
	vmovups	%xmm0, (%rcx)           # main.cpp:53
	addq	$24, %rcx               # main.cpp:53
	movq	%rax, %rdx              # main.cpp:53
	subq	%rcx, %rdx              # main.cpp:53
	addq	$6151, %rdx             # main.cpp:53
                                        # imm = 0x1807
	cmpq	$7, %rdx                # main.cpp:53
	ja	.LBBmain_1              # main.cpp:53
# BB#2:                                 # %"ipa_lbl$117"
	movq	%rsp, %rax
	addq	$6272, %rax             # imm = 0x1880
	movq	%rax, %rcx
	.p2align	5, 0x90
.LBBmain_3:                             # %"file main.cpp, line 54, in inner loop at depth 0, bb11185"
                                        # =>This Inner Loop Header: Depth=1
	.loc	1  54  0
	movq	112(%rsp), %rdx         # main.cpp:54
	movq	%rdx, 16(%rcx)          # main.cpp:54
	vmovaps	96(%rsp), %xmm0         # main.cpp:54
	vmovups	%xmm0, (%rcx)           # main.cpp:54
	addq	$24, %rcx               # main.cpp:54
	movq	%rax, %rdx              # main.cpp:54
	subq	%rcx, %rdx              # main.cpp:54
	addq	$6151, %rdx             # main.cpp:54
                                        # imm = 0x1807
	cmpq	$7, %rdx                # main.cpp:54
	ja	.LBBmain_3              # main.cpp:54
# BB#4:                                 # %"ipa_lbl$126"
	.loc	1  62  0
#SK: loop boundary for outer loop in ebx
	movl	$10000000, %ebx         # main.cpp:62
                                        # imm = 0x989680
#SK: subtract argc from nLoop
	subl	%edi, %ebx              # main.cpp:62
	.loc	1  58  0
	xorb	%al, %al                # main.cpp:58
	callq	_ZNSt6chrono3_V212system_clock3nowEv # main.cpp:58
	.loc	1  44  0
	movq	%rax, 18568(%rsp)       # main.cpp:44
	.loc	1  62  0
	testl	%ebx, %ebx              # main.cpp:62
	jle	.LBBmain_11             # main.cpp:62
# BB#5:                                 # %"file main.cpp, line 62, bb51"
	xorl	%eax, %eax
#SK: nLoop now in r8
	movslq	%ebx, %r8               # main.cpp:62
	.p2align	5, 0x90
.LBBmain_6:                             # %"@cfe_1377$main"
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB1_7 Depth 2
                                        #       Child Loop BB1_8 Depth 3
#SK: outer loop start (n=0 ... 10000000)
	xorl	%edx, %edx  #SK: int n, stored in edx
	xorl	%esi, %esi  #SK: additional counter variable increased in steps of 3
	.p2align	5, 0x90
.LBBmain_7:                             # %"ipa_lbl$135"
                                        #   Parent Loop BB1_6 Depth=1
                                        # =>  This Loop Header: Depth=2
                                        #       Child Loop BB1_8 Depth 3
#SK: inner loop start (i=0 ... 255)
	.loc	1  63  0
#SK: x-component, load A[..]
	vmovsd	128(%rsp,%rsi,8), %xmm0 # main.cpp:63
                                        # xmm0 = mem[0],zero
#SK: x-component, subract B[..]
	vsubsd	6272(%rsp,%rsi,8), %xmm0, %xmm0 # main.cpp:63
#SK: x-component, save result to C_temp[..]
	vmovsd	%xmm0, 18576(%rsp)      # main.cpp:63
#SK: y-component, ...
	vmovsd	136(%rsp,%rsi,8), %xmm0 # main.cpp:63
                                        # xmm0 = mem[0],zero
	vsubsd	6280(%rsp,%rsi,8), %xmm0, %xmm0 # main.cpp:63
	vmovsd	%xmm0, 18584(%rsp)      # main.cpp:63
#SK: z-component, ...
	vmovsd	144(%rsp,%rsi,8), %xmm0 # main.cpp:63
                                        # xmm0 = mem[0],zero
	vsubsd	6288(%rsp,%rsi,8), %xmm0, %xmm0 # main.cpp:63
	vmovsd	%xmm0, 18592(%rsp)      # main.cpp:63
	xorl	%edi, %edi
	.p2align	5, 0x90
.LBBmain_8:                             # %"file main.cpp, line 63, in inner loop at depth 2, bb41186"
                                        #   Parent Loop BB1_6 Depth=1
                                        #     Parent Loop BB1_7 Depth=2
                                        # =>    This Inner Loop Header: Depth=3
#SK: loop i=0,1,2 to save C_temp[0,1,2] into C[..+1,2,3]
	leaq	(%rdi,%rsi), %rbx       # main.cpp:63
	movq	18576(%rsp,%rdi,8), %rcx # main.cpp:63
	movq	%rcx, 12416(%rsp,%rbx,8) # main.cpp:63
	incq	%rdi                    # main.cpp:63
	cmpq	$3, %rdi                # main.cpp:63
	jl	.LBBmain_8              # main.cpp:63
# BB#9:                                 # %"file main.cpp, line 63, in loop at depth 1, bb29"
                                        #   in Loop: Header=BB1_7 Depth=2
#SK: increase additional counter used for array indexing
	addq	$3, %rsi                # main.cpp:63

#SK: n+=1 (rdx is the 64-bit version) of edx)
	incq	%rdx                    # main.cpp:63
#SK 
	cmpq	$256, %rdx              # main.cpp:63
                                        # imm = 0x100
	jl	.LBBmain_7              # main.cpp:63
# BB#10:                                # %"file main.cpp, line 62, in loop at depth 0, bb33"
                                        #   in Loop: Header=BB1_6 Depth=1
	.loc	1  62  0
#SK: increase n by 1
	incq	%rax                    # main.cpp:62
	cmpq	%r8, %rax               # main.cpp:62
#SK: outer loop end
	jl	.LBBmain_6              # main.cpp:62


.LBBmain_11:                            # %"@cfe_1378$main"
	.loc	1  66  0
	xorb	%al, %al                # main.cpp:66
	callq	_ZNSt6chrono3_V212system_clock3nowEv # main.cpp:66
	subq	18568(%rsp), %rax       # main.cpp:66
	movabsq	$4835703278458516699, %rcx # main.cpp:66
                                        # imm = 0x431BDE82D7B634DB
	imulq	%rcx                    # main.cpp:66
	movq	%rdx, %rax              # main.cpp:66
	shrq	$63, %rax               # main.cpp:66
	shrq	$18, %rdx               # main.cpp:66
	leal	(%rdx,%rax), %ebx       # main.cpp:66
	.loc	1  68  0
	movl	$_ZSt4cout, %edi        # main.cpp:68
	movl	$initialized$$$CFE_id_7fb21f52_1c4b7d34+8, %esi # main.cpp:68
	xorb	%al, %al                # main.cpp:68
	callq	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc # main.cpp:68
	movq	%rax, %rcx              # main.cpp:68
	xorb	%al, %al                # main.cpp:68
	movq	%rcx, %rdi              # main.cpp:68
	movl	%ebx, %esi              # main.cpp:68
	callq	_ZNSolsEi               # main.cpp:68
	movq	%rax, %rcx              # main.cpp:68
	movl	$initialized$$$CFE_id_7fb21f52_1c4b7d34+24, %esi # main.cpp:68
	xorb	%al, %al                # main.cpp:68
	movq	%rcx, %rdi              # main.cpp:68
	callq	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc # main.cpp:68
	movq	%rax, %rcx              # main.cpp:68
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi # main.cpp:68
	xorb	%al, %al                # main.cpp:68
	movq	%rcx, %rdi              # main.cpp:68
	callq	_ZNSolsEPFRSoS_E        # main.cpp:68
	.loc	1  69  0
	vmovsd	12416(%rsp), %xmm0      # main.cpp:69
                                        # xmm0 = mem[0],zero
	movl	$_ZSt4cout, %edi        # main.cpp:69
	movb	$1, %al                 # main.cpp:69
	callq	_ZNSolsEd               # main.cpp:69
	movq	%rax, %rcx              # main.cpp:69
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi # main.cpp:69
	xorb	%al, %al                # main.cpp:69
	movq	%rcx, %rdi              # main.cpp:69
	callq	_ZNSolsEPFRSoS_E        # main.cpp:69
	.loc	1  70  0
	xorl	%eax, %eax              # main.cpp:70
	movq	%rbp, %rsp              # main.cpp:70
	addq	$-8, %rsp               # main.cpp:70
	popq	%rbx                    # main.cpp:70
	popq	%rbp                    # main.cpp:70
	retq                            # main.cpp:70
..TxtEnd_F2:
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc

	.globl	__sti___7fb21f52_1c4b7d34
	.p2align	5, 0x90
	.type	__sti___7fb21f52_1c4b7d34,@function
__sti___7fb21f52_1c4b7d34:              # @__sti___7fb21f52_1c4b7d34
	.cfi_startproc
..TxtBeg_F3:
	.loc	1  0  0
# BB#0:                                 # %", bb1"
	.loc	1  74  0
	pushq	%rax                    # main.cpp:74
.Lcfi4:
	.cfi_def_cfa_offset 16
	movl	$uninitialized$$$CFE_id_7fb21f52_1c4b7d34, %edi # main.cpp:74
	xorb	%al, %al                # main.cpp:74
	callq	_ZNSt8ios_base4InitC1Ev # main.cpp:74
	movl	$_ZNSt8ios_base4InitD1Ev, %edi # main.cpp:74
	movl	$uninitialized$$$CFE_id_7fb21f52_1c4b7d34, %esi # main.cpp:74
	movl	$__dso_handle, %edx     # main.cpp:74
	xorb	%al, %al                # main.cpp:74
	popq	%rcx                    # main.cpp:74
	jmp	__cxa_atexit            # main.cpp:74
                                        # TAILCALL
..TxtEnd_F3:
.Lfunc_end2:
	.size	__sti___7fb21f52_1c4b7d34, .Lfunc_end2-__sti___7fb21f52_1c4b7d34
	.cfi_endproc

	.type	cfe_static_2911$$CFE_id_7fb21f52_1c4b7d34,@object # @"@cfe_static_2911$$CFE_id_7fb21f52_1c4b7d34"
	.section	.init_array,"aw",@init_array
	.globl	cfe_static_2911$$CFE_id_7fb21f52_1c4b7d34
	.p2align	3
cfe_static_2911$$CFE_id_7fb21f52_1c4b7d34:
	.quad	__sti___7fb21f52_1c4b7d34
	.size	cfe_static_2911$$CFE_id_7fb21f52_1c4b7d34, 8

	.type	initialized$$$CFE_id_7fb21f52_1c4b7d34,@object # @"initialized$$$CFE_id_7fb21f52_1c4b7d34"
	.data
	.p2align	6
initialized$$$CFE_id_7fb21f52_1c4b7d34:
	.quad	0                       # 0x0
	.quad	2334102053365836869     # 0x2064657370616c45
	.quad	35435181861236          # 0x203a656d6974
	.quad	544435488               # 0x20736d20
	.quad	256                     # 0x100
	.quad	__pthread_key_create
	.quad	0                       # 0x0
	.size	initialized$$$CFE_id_7fb21f52_1c4b7d34, 56

	.type	uninitialized$$$CFE_id_7fb21f52_1c4b7d34,@object # @"uninitialized$$$CFE_id_7fb21f52_1c4b7d34"
	.local	uninitialized$$$CFE_id_7fb21f52_1c4b7d34
	.comm	uninitialized$$$CFE_id_7fb21f52_1c4b7d34,8,64
	.type	initialized$main$$CFE_id_7fb21f52_1c4b7d34,@object # @"initialized$main$$CFE_id_7fb21f52_1c4b7d34"
	.local	initialized$main$$CFE_id_7fb21f52_1c4b7d34
	.comm	initialized$main$$CFE_id_7fb21f52_1c4b7d34,16,64

	.section	".note.GNU-stack","",@progbits
