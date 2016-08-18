#include "../show.h"

struct A {
    int &x;
    A(int &x) : x(x) {}

    int& get() { return x;}
};

struct B {
    int x;
    B(int x) : x(x) {}

    int get() { return x;}
};

void test() {
    int x=10;
    A a(x);
    B b(x);

    {
        SHOW(a.x);
        auto y = a.get();
        y += 1;
        SHOW(a.x);

        SHOW(a.x);
        decltype(auto) z = a.get();
        z += 1;
        SHOW(a.x);
    }

    {
        SHOW(b.x);
        auto y = b.get();
        y += 1;
        SHOW(b.x);

        SHOW(b.x);
        decltype(auto) z = b.get();
        z += 1;
        SHOW(b.x);
    }
}

int main() {
    test();
}
