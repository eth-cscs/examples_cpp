#include "../show.h"

struct X {
    int a = 10;
    int b = 22;

    X() = default;
    X(int x) : a(x) {}
};

int main () {
    X x(34);
    SHOW(x.a);
    SHOW(x.b);

    X y;
    SHOW(y.a);
    SHOW(y.b);

};
