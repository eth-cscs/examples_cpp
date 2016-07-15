#include "../show.h"

template <typename ...T>
using void_t = void;

template <class C>
using can_add = decltype(std::declval<C>()+std::declval<C>());


template <typename T, typename VOID=void> // this "void" is idiomatic
struct sum {
    static T add(T const&,T const&) { std::cout << "No operator found "; return T{};}
};

template <typename T>
struct sum<T, void_t<can_add<T>>> {
    static T add(T const& a, T const& b) {
        return a+b;
    }
};


struct A {};

std::ostream& operator<<(std::ostream& s, A) {
    return s << "A";
}

struct B {
    std::string s;
    B(std::string s) : s{s} {}
};

B operator+(B const& x, B const& y) {return B{x.s + " " + y.s};}

std::ostream& operator<<(std::ostream& s, B const& x) {
    return s << x.s;
}

int main() {
    SHOW(sum<int>::add(3,4))
    SHOW(sum<A>::add(A{}, A{}))
    SHOW(sum<B>::add(B{"Hello"}, B{"World"}))
}