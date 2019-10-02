#include <iostream>
#include <string>


namespace X {

    struct A {};

    void foo(A) {
        std::cout << "I'm X\n";
    }
}

namespace Y {

    struct A {};

    void foo(A) {
        std::cout << "I'm Y\n";
    }
}


template <typename T>
void bar(T const& x) {
    foo(x);
}

int main() {
    X::A xa;
    Y::A ya;

    bar(xa);
    bar(ya);

}
