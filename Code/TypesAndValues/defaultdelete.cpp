#include "../show.h"

struct X {
    int a = 42;
    X() = default;

    X& operator=(X&& other) = delete;
};

struct X1 {
    int a = 42;
    X1() = default;

    X1(X1 const& other) = default;
    X1& operator=(X1&& other) = delete;
};

struct Y {
    int a = 42;
    Y() = default;
    Y(int) {}
};

void foo(int) = delete;

int main() {
    X x{};

    //X y(x); automatic copy constructor deleted by move assignment
    X1 x1{};

    X1 y1(x1);

    Y u{};
    Y w(u);
    SHOW(u.a);
    SHOW(w.a);
    Y s(100);
    SHOW(s.a);

    //foo(4);
}
