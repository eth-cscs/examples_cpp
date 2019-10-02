#include <iostream>

/* 1 */ int    foo(int, int) {std::cout << __PRETTY_FUNCTION__ << "\n"; return 0;}

/* 2 */ double foo(int, float) {std::cout << __PRETTY_FUNCTION__ << "\n"; return 0.;}

template <typename T>
/* 3 */ char foo(T, int) {std::cout << __PRETTY_FUNCTION__ << "\n"; return '\n';}

int main() {
    /* A */ foo(3,4);

    /* B */ //foo(3,4.3);

    /* C */ foo(3.4,4);

    /* D */ foo(3.4f,4);

    /* E */ foo(3.4,4.5);

    /* F */ //foo(3.4f,4.5f);
}
