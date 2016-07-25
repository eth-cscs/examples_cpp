#include "../show.h"

struct A {
    A() { std::cout << "Default constuctor of A\n";}
};

struct B {
    int a, b, c;
    B() = delete;
};

OUT(B) {
    return s << a.a << " " << a.b << " " << a.c;
}


struct C {
    C(int x=10) { std::cout << "Not(!) default constructor of C\n";}
};

void test() {
    int i; // default initialized to indeterminate
    int j{}; // zero initialized

    A a; // default constructed by calling default constructor
    A b{}; // default constructed though overload resolution
//    B c; // default constructor cannot be called! Error
    B d{}; // B is an aggregate (even with deleted constructors)
    SHOW(d);

    C e; // Overload resolution of C() // N4537 8.5.17.6
    C f{}; // default constructed though overload resolution
}

int main() {
    test();
}