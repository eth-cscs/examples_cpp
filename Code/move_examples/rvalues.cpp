#include <type_traits>
#include "../show.h"

int f(int &x) {
    std::cout << "int&\n";
    return x;
}

int f(int&& x) {
    std::cout << "int&&\n";
    return x;
}

struct A {
    void operator()() & {
        std::cout << "A&\n";
    }

    void operator()() && {
        std::cout << "A&&\n";
    }
};

int main() {
    int x = 10;
    f(x);
    f(10);

    A a;
    a();
    A()();
}
