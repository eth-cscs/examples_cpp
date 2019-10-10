#include "library.hpp"

void foo(int a, int b, int c, pair<int,int> p) {
    f(p);
}


int main() {
    int a, b, c;

    pair<int, int> p{42, 42};

    int d, e, g;

    foo(a,b,g,p);
}

/*
 COMPILER EXPLORER
    EXPLICIT CONSTRUCTOR
        mov     rax, QWORD PTR [rbp-32]
        mov     QWORD PTR [rbp-24], rax
        lea     rax, [rbp-24]
        mov     rdi, rax
        call    f(pair<int, int>)
        lea     rax, [rbp-24]
        mov     rdi, rax
        call    pair<int, int>::~pair() [complete object destructor]
    DEFAULT CONSTRUCTOR
        mov     rax, QWORD PTR [rbp-8]
        mov     rdi, rax
        call    f(pair<int, int>)
