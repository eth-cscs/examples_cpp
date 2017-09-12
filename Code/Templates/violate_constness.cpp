#include <iostream>
#include "../show.h"

template <typename T>
int inc(T const& x) {
    return ++x;
}

int main() {
    int y = 10;

    // foo(10): does not compile since ++x requires a mutable object
    // foo(y): does not compile since ++x requires a mutable object

    SHOW(inc<int&>(y));
    SHOW(y);
}
