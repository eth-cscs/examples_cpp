#include "../show.h"

struct A {
    A() { std::cout << "Default constuctor of A\n";}
};

struct B {
    int a, b, c;
    B() = delete;
};

struct C {
    C(int x=10) { std::cout << "Not(!) default constructor of C\n";}
};

void test() {
    int i; // default initialized to indeterminate
    int j{}; // zero initialized

    A a; // default constructed by calling default constructor
    A b{}; // default constructed though overload resolution
//    B c; // default constructor cannot be called! Error
    B d{}; // Default initialized : indeterminate values
    SHOW(d.a);

    C e; // Overload resolution of C() // N4537 8.5.17.6
    C f{}; // default constructed though overload resolution
}

int main() {
    test();
}