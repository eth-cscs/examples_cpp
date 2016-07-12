#include <iostream>

// Primary template
template <typename T, typename U>
struct X {
    X() { std::cout << "Primary\n";}
};

// Specialization 1
template <typename T>
struct X<T, int> {
    X() { std::cout << "Specialization 1\n";}
};

// Specialization 2
template <typename U>
struct X<float, U> {
    X() { std::cout << "Specialization 2\n";}
};

template <>
struct X<float, int> {
    X() { std::cout << "Full specialization\n";}
};
int main() {
    X<char, double> a; // primary template
    X<char, int> b; // Specialization 1
    X<float, double> c; // specialization 2
    X<float, int> d; // error: ambiguous partial specializations of 'X<float, int>'
}
