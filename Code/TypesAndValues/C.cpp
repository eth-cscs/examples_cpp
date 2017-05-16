#include <iostream>

struct C {
    C(int) { std::cout << "C(int)\n"; }
    C(int, int) { std::cout << "C(int)\n"; }
    C(std::initializer_list<int> && ) { std::cout << "C(std::initializer_list<int>&&)\n"; }
};

int main() {
    C a(10);
    C b{10};
}
