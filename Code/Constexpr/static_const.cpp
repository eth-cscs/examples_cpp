#include <iostream>

int foo(int a) { return a*a; };
constexpr int fooc(int a) { return a*a; };

static const int x = fooc(10);

constexpr int y = fooc(10);

int main() {
    std::cout << x << "\n";
    std::cout << y << "\n";
}
