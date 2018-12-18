# DAINT

Code description
----------------
The code defines a small Vector3D structure of 3 doubles and an associated
'operator-' to perform a subtraction on each component of the Vector3D.  An
alias Vector3DField is used to define a container of Vector3D based on
std::array.  Function 'subtract' is performing the element-wise subtraction of
the container.

Problem
-------
Explain why gcc is faster than the other compilers (not being able to vectorize
the subtraction on Vector3D)


* ok = compiles and runs
* mll daint-mc
* ~/sbatch.sh dom 2 bin/dom_GNU_4.9.3.exe 1 1 1 1 1 -Cmc "" "" "" "" $SCRATCH/

## bug1

* -O3 -std=c++14

effo_dom_GNU_7.3.0_broadwell.exe.1.1.1.1.1.htno-dom.david:Elapsed time: 978 ms  <--- best
effo_dom_GNU_5.3.0_broadwell.exe.1.1.1.1.1.htno-dom.david:Elapsed time: 982 ms
effo_dom_GNU_6.2.0_broadwell.exe.1.1.1.1.1.htno-dom.david:Elapsed time: 982 ms
effo_dom_CLANG_7.0.0_broadwell.exe.1.1.1.1.1.htno-dom.david:Elapsed time: 2389 ms
effo_dom_CRAY_8.6.1_broadwell.exe.1.1.1.1.1.htno-dom.david:Elapsed time: 2439 ms
effo_dom_INTEL_17.0.4.196_broadwell.exe.1.1.1.1.1.htno-dom.david:Elapsed time: 3534 ms
effo_dom_INTEL_18.0.2.199_broadwell.exe.1.1.1.1.1.htno-dom.david:Elapsed time: 3536 ms
effo_dom_PGI_18.5_broadwell.exe.1.1.1.1.1.htno-dom.david:Elapsed time: 7151 ms
effo_dom_CRAY_8.7.3_broadwell.exe.1.1.1.1.1.htno-dom.david:Elapsed time: 14921 ms
effo_dom_CRAY_9.0.0.21672_broadwell.exe.1.1.1.1.1.htno-dom.david:Elapsed time: 14925 ms

effo_dom_CRAY_8.6.1_broadwell.exe.1.1.1.1.1.htno-dom.david:Elapsed time: 2440 ms       # -O2
effo_dom_CRAY_8.7.3_broadwell.exe.1.1.1.1.1.htno-dom.david:Elapsed time: 7040 ms       # -O2
effo_dom_CRAY_9.0.0.21672_broadwell.exe.1.1.1.1.1.htno-dom.david:Elapsed time: 7040 ms # -O2

### CRAY listing:
     Primary Loop Type        Modifiers
     ------- ---- ----        ---------
     A - Pattern matched      a - atomic memory operation
                              b - blocked
     C - Collapsed            c - conditional and/or computed
     D - Deleted
     E - Cloned
     F - Flat - No calls      f - fused
     G - Accelerated          g - partitioned
     I - Inlined              i - interchanged
     M - Multithreaded        m - partitioned
                              n - non-blocking remote transfer
                              p - partial
     R - Rerolling            r - unrolled
                              s - shortloop
     V - Vectorized           w - unwound

### CRAY_87.lst:
   61.                     int const nLoop = 10000000 - argc; // unpredictable loop count
   62.  + iF-------------<     for(int n=0; n<nLoop; n++)
   63.  + iF i I-------<>>       subtract(fieldVecA, fieldVecB, fieldVecC);

CC-6296 CC: VECTOR main, File = main.cpp, Line = 62
  A loop was not vectorized because it contains an inner loop where a "#pragma _CRI ivdep" or "concurrent" directive was specified.

CC-6007 CC: SCALAR main, File = main.cpp, Line = 62
  A loop was interchanged with the loop starting at line 63.

CC-3182 CC: IPA main, File = main.cpp, Line = 62, Column = 5
  Loop has been flattened.

CC-6315 CC: VECTOR main, File = main.cpp, Line = 63
  A loop was not vectorized because the target array (subtraction) would require rank expansion.
explain CC-6315
VECTOR: A loop was not vectorized because the target array (%s) would require
rank expansion.
When vectorizing a loop some scalar objects must be promoted to arrays. In
some contexts an array element is effectively a scalar and so poses no
problem to vectorization. There are other contexts in which an array must be
expanded to a higher rank array in order to vectorize. Though possible in
theory, such a transformation is very costly, and so rank expansion of arrays
is not supported. A small example of this issue occurs with the J-loop
below:
      DO J = 1, N
         A(1) = J
         A(2) = 2*J
         A(3) = 5*J
         do I = 1, 3
            B(I) = A(I)*A(I)
         enddo
      ENDDO
In some codes, like the preceeding, selective unwinding of inner loops can
avoid the array expansion problem.  An unroll directive that specifies the
full trip count of a loop acts as a command to unwind said loop.  Both the
trip count of the loop and the unroll amount must be known at compile time.
Care should be taken when unwinding inner loops to avoid array expansion.
This technique can lead to long compile times and very high vector register
pressure.  When the compiler is able to manage the register pressure well
this is often an effective method to improve memory/compute balance.

### CRAY_86.lst:
   61.                     int const nLoop = 10000000 - argc; // unpredictable loop count
   62.  + F----------<     for(int n=0; n<nLoop; n++)
   63.  + F r8 I---<>>       subtract(fieldVecA, fieldVecB, fieldVecC);

CC-6294 CC: VECTOR main, File = main.cpp, Line = 62
  A loop was not vectorized because a better candidate was found at line 63.

CC-3182 CC: IPA main, File = main.cpp, Line = 62, Column = 5
  Loop has been flattened.

CC-6332 CC: VECTOR main, File = main.cpp, Line = 63
  A loop was not vectorized because it does not map well onto the target architecture.
explain CC-6332
VECTOR:  A loop was not vectorized because it does not map well onto the
target architecture.
The loop contains too many operations that have no clean vector equivalent in
hardware for the targeted architecture, and has been left to run as a purely
scalar loop.  Although the loop is vectorizable from a dependency and idiom
standpoint, it would be unprofitable to emulate vector execution using scalar
operations.
On other architectures with different hardware capabilities, this loop may be
cleanly vectorized.


CC-6005 CC: SCALAR main, File = main.cpp, Line = 63
  A loop was unrolled 8 times.

CC-3001 CC: IPA main, File = main.cpp, Line = 63, Column = 7
  The call to tiny routine "subtract" was textually inlined and flattened.

Assembly
--------

Extract from function 'subtract(...)'

> objdump -d ./main

* gcc: we can see subpd SIMD subtract instruction and confirmed by computation time (2 times faster)

0000000000400ab0 <_Z8subtractRKSt5arrayI8Vector3DLm256EES3_RS1_>:
  400ab0:	48 8d 4e 30             lea    0x30(%rsi),%rcx
  400ab4:	48 8d 42 30             lea    0x30(%rdx),%rax
  400ab8:	48 39 ca                cmp    %rcx,%rdx
  400abb:	41 0f 93 c0             setae  %r8b
  400abf:	48 39 c6                cmp    %rax,%rsi
  400ac2:	0f 93 c1                setae  %cl
  400ac5:	41 08 c8                or     %cl,%r8b
  400ac8:	74 60                   je     400b2a <_Z8subtractRKSt5arrayI8Vector3DLm256EES3_RS1_+0x7a>
  400aca:	48 8d 4f 30             lea    0x30(%rdi),%rcx
  400ace:	48 39 ca                cmp    %rcx,%rdx
  400ad1:	0f 93 c1                setae  %cl
  400ad4:	48 39 c7                cmp    %rax,%rdi
  400ad7:	0f 93 c0                setae  %al
  400ada:	08 c1                   or     %al,%cl
  400adc:	74 4c                   je     400b2a <_Z8subtractRKSt5arrayI8Vector3DLm256EES3_RS1_+0x7a>
  400ade:	31 c0                   xor    %eax,%eax
  400ae0:	66 0f 10 44 06 10       movupd 0x10(%rsi,%rax,1),%xmm0
  400ae6:	66 0f 10 4c 07 10       movupd 0x10(%rdi,%rax,1),%xmm1
  400aec:	66 0f 10 54 06 20       movupd 0x20(%rsi,%rax,1),%xmm2
  400af2:	66 0f 5c c8             subpd  %xmm0,%xmm1
  400af6:	66 0f 10 44 07 20       movupd 0x20(%rdi,%rax,1),%xmm0
  400afc:	66 0f 10 1c 06          movupd (%rsi,%rax,1),%xmm3
  400b01:	66 0f 5c c2             subpd  %xmm2,%xmm0
  400b05:	66 0f 10 14 07          movupd (%rdi,%rax,1),%xmm2
  400b0a:	66 0f 5c d3             subpd  %xmm3,%xmm2
  400b0e:	0f 11 4c 02 10          movups %xmm1,0x10(%rdx,%rax,1)
  400b13:	0f 11 44 02 20          movups %xmm0,0x20(%rdx,%rax,1)
  400b18:	0f 11 14 02             movups %xmm2,(%rdx,%rax,1)
  400b1c:	48 83 c0 30             add    $0x30,%rax
  400b20:	48 3d 00 18 00 00       cmp    $0x1800,%rax
  400b26:	75 b8                   jne    400ae0 <_Z8subtractRKSt5arrayI8Vector3DLm256EES3_RS1_+0x30>
  400b28:	f3 c3                   repz retq
  400b2a:	31 c0                   xor    %eax,%eax
  400b2c:	0f 1f 40 00             nopl   0x0(%rax)
  400b30:	f2 0f 10 4c 07 08       movsd  0x8(%rdi,%rax,1),%xmm1
  400b36:	f2 0f 10 44 07 10       movsd  0x10(%rdi,%rax,1),%xmm0
  400b3c:	f2 0f 10 14 07          movsd  (%rdi,%rax,1),%xmm2
  400b41:	f2 0f 5c 4c 06 08       subsd  0x8(%rsi,%rax,1),%xmm1
  400b47:	f2 0f 5c 44 06 10       subsd  0x10(%rsi,%rax,1),%xmm0
  400b4d:	f2 0f 5c 14 06          subsd  (%rsi,%rax,1),%xmm2
  400b52:	f2 0f 11 4c 02 08       movsd  %xmm1,0x8(%rdx,%rax,1)
  400b58:	f2 0f 11 44 02 10       movsd  %xmm0,0x10(%rdx,%rax,1)
  400b5e:	f2 0f 11 14 02          movsd  %xmm2,(%rdx,%rax,1)
  400b63:	48 83 c0 18             add    $0x18,%rax
  400b67:	48 3d 00 18 00 00       cmp    $0x1800,%rax
  400b6d:	75 c1                   jne    400b30 <_Z8subtractRKSt5arrayI8Vector3DLm256EES3_RS1_+0x80>
  400b6f:	f3 c3                   repz retq
  400b71:	66 2e 0f 1f 84 00 00    nopw   %cs:0x0(%rax,%rax,1)
  400b78:	00 00 00
  400b7b:	0f 1f 44 00 00          nopl   0x0(%rax,%rax,1)



* icc: only subsd scalar instruction

00000000004012d0 <_Z8subtractRKSt5arrayI8Vector3DLm256EES3_RS1_>:
  4012d0:	33 c0                   xor    %eax,%eax
  4012d2:	8d 0c 00                lea    (%rax,%rax,1),%ecx
  4012d5:	ff c0                   inc    %eax
  4012d7:	4c 8d 14 49             lea    (%rcx,%rcx,2),%r10
  4012db:	f2 42 0f 10 04 d7       movsd  (%rdi,%r10,8),%xmm0
  4012e1:	f2 42 0f 10 4c d7 08    movsd  0x8(%rdi,%r10,8),%xmm1
  4012e8:	f2 42 0f 10 54 d7 10    movsd  0x10(%rdi,%r10,8),%xmm2
  4012ef:	f2 42 0f 5c 04 d6       subsd  (%rsi,%r10,8),%xmm0
  4012f5:	f2 42 0f 5c 4c d6 08    subsd  0x8(%rsi,%r10,8),%xmm1
  4012fc:	f2 42 0f 5c 54 d6 10    subsd  0x10(%rsi,%r10,8),%xmm2
  401303:	66 0f 14 c1             unpcklpd %xmm1,%xmm0
  401307:	66 49 0f 7e d0          movq   %xmm2,%r8
  40130c:	42 0f 11 04 d2          movups %xmm0,(%rdx,%r10,8)
  401311:	4e 89 44 d2 10          mov    %r8,0x10(%rdx,%r10,8)
  401316:	f2 42 0f 10 6c d7 28    movsd  0x28(%rdi,%r10,8),%xmm5
  40131d:	f2 42 0f 10 5c d7 18    movsd  0x18(%rdi,%r10,8),%xmm3
  401324:	f2 42 0f 10 64 d7 20    movsd  0x20(%rdi,%r10,8),%xmm4
  40132b:	f2 42 0f 5c 6c d6 28    subsd  0x28(%rsi,%r10,8),%xmm5
  401332:	f2 42 0f 5c 5c d6 18    subsd  0x18(%rsi,%r10,8),%xmm3
  401339:	f2 42 0f 5c 64 d6 20    subsd  0x20(%rsi,%r10,8),%xmm4
  401340:	66 49 0f 7e e9          movq   %xmm5,%r9
  401345:	66 0f 14 dc             unpcklpd %xmm4,%xmm3
  401349:	42 0f 11 5c d2 18       movups %xmm3,0x18(%rdx,%r10,8)
  40134f:	4e 89 4c d2 28          mov    %r9,0x28(%rdx,%r10,8)
  401354:	3d 80 00 00 00          cmp    $0x80,%eax
  401359:	0f 82 73 ff ff ff       jb     4012d2 <_Z8subtractRKSt5arrayI8Vector3DLm256EES3_RS1_+0x2>
  40135f:	c3                      retq

