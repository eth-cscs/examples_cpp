#include <iostream>

template <typename T, typename U = int>
struct X {
    X() { std::cout << "value type\n";}
};

template <typename T>
struct X<T, typename T::extra_type> {
    X() { std::cout << "extra type\n";}
};

struct A {
    using value_type = int;
};

struct B {
    using extra_type = int;
};

struct C {
    using extra_type = float;
};

struct D {
    using extra_type = char;
};

int main() {
    X<A> a; // Specialization is discarded due to SFINAE
    X<B> b; // Specialization is taken
    X<C> c; // C::extra_type is not int
    X<B,char> b1; // B::extra_type is int, but char is the second argument
    X<D,char> d; // <D, D::extra_type> is more specialized!
}
