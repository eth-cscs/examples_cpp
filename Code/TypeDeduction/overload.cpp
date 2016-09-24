#include <iostream>

int    foo(int, int) {std::cout << __PRETTY_FUNCTION__ << "\n"; return 0;}

double foo(float, int) {std::cout << __PRETTY_FUNCTION__ << "\n"; return 0.;}

template <typename T>
char foo(T, int) {std::cout << __PRETTY_FUNCTION__ << "\n"; return '\n';}

int main() {
    foo(3,4);
    foo(3,4.3);
    foo(3.4,4);
    foo(3.4f,4);
    foo(3.4,4.5);
    foo(3.4f,4.5f);
}
