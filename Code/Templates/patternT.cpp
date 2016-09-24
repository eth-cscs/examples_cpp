#include <iostream>

template <typename T, typename U>
struct X {
    X() {std::cout << "primary\n";}
};


template <typename T, typename U>
struct X<T, X<T,U>> {
    X() {std::cout << "specialization\n";}
};

template <typename T>
void foo(X<T,T>) {
    std::cout << "foo\n";
}

int main() {
    X<int, int> x1;
    X<int, X<int,float>> x2;
    X<int, X<char,X<int,void>>> x3;

    foo(x1);
}
