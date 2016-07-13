#include <iostream>
#include "../show.h"

void f(int) { std::cout << "Never run!\n";}

namespace A {
    struct X {};
    struct Y {
        int i = 4;
        Y() {}
        Y(int v) : i(v) {}
        Y operator-(Y const& v) const {
            return Y(i-v.i);
        }
    };
    void f(int) {}
    void g(X) {}
}

std::ostream& operator<<(std::ostream& s, A::Y const& y) {
    return s << " Y(" << y.i << ")";
}

namespace B {
    void f(int i) {
        SHOW(i);
        if (i>0) f(i-1);   // calls B::f (endless recursion)
    }
    void g(A::X x) {
        //g(x);   // Error: ambiguous between B::g (ordinary lookup)
        //        and A::g (argument-dependent lookup)
    }
    void h(A::Y y) {
        SHOW(y);
        if (y.i>0) h(y-1);   // calls B::h (endless recursion): ADL examines the A namespace
        // but finds no A::h, so only B::h from ordinary lookup is used
    }
}


int main() {
    B::f(3);
    B::g(A::X{});
    B::h(A::Y{});
}