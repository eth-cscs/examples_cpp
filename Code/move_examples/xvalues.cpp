#include <iostream>
#include <typeinfo>
#include <algorithm>

struct A {
    int m;

    A(int m) :m(m) {}

    A(A const&) = delete;
};

std::ostream& operator<<(std::ostream& s, A const& a) {
    return s << a.m;
}

bool operator<(A const& a, A const& b) {
    return a.m < b.m;
}

A&& operator+(A const& a ,A const& b) {
    return std::move(A(a.m + b.m));
}

void foo(A const& x) {
    std::cout << "A & " << x.m << std::endl;
}

void foo(A && x) {
    std::cout << "A && " << x.m << std::endl;
}


int main() {

    A a(10), b(20);

    std::cout << ((a+b).m) << std::endl;


    A&& ar = std::move(a);

    ar.m = 14;

    std::cout << a.m << " == " << ar.m << std::endl;

    foo(a);
    foo(ar);
    foo(std::move(ar));

    std::cout << typeid(decltype(a)).name() << std::endl;

    std::cout << typeid(decltype(ar)).name() << std::endl;

    std::cout << "min " << std::min(a,A(7)) << std::endl;

    A const& y = std::min(a,A(7));

    std::cout << "the out " << y << std::endl;
    return 0;
}
