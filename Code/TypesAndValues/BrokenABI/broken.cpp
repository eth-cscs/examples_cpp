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

