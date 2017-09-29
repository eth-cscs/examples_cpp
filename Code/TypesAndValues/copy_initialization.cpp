#include "../show.h"

struct A {
    int a;
    int b = 10;
    explicit A(int x) :a(x) {}
    explicit A(int x, int y) :a(x), b(y) {}
    explicit operator int() {return a;}
};

struct B {
    int a;
    int b = 10;
    B(int x) : a(x) {}
    B(int x, int y) : a(x), b(y) {}
    operator int() {return a;}
};

B make_B(int a, int b) {
    return {a,b};
}

A make_A(int a, int b) {
    return A{a,b};
}

void take_B(B x) {
    SHOW_PREFIX("In take_B I receive: ", x.a);
}

struct C {
    int a;
    explicit C(int x): a{x} {std::cout << "hello C\n";}
};

void testB() {
    B x = 10.;
    SHOW(x.a);

    take_B(42);

    B y = {34,45}; // calling B(int, int)
    SHOW(make_B(45,67).a);

    int i = y;
}

void testA() {
    A x(10.);
    SHOW(x.a);

    A y{34,45};
    SHOW(make_A(45,67).a);

    int i = static_cast<int>(y);
}

int main() {
    testB();
    testA();
    C a = static_cast<C>(10);
}
