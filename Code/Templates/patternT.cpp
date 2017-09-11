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
    std::cout << "foo<T,T>\n";
}

template <typename T, typename U>
void foo(X<T,U>) {
    std::cout << "foo<T,U>\n";
}

int main() {
    X<int, int> x1;
    X<int, X<int,float>> x2;
    X<int, X<char,X<int,void>>> x3;

    foo(x1);
    foo(x3);
}
