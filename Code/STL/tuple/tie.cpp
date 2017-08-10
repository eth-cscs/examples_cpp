#include <iostream>
#include <tuple>
#include "../../show.h"
class A {
    int a;

public:
    A(int a) : a{a} {}

    A(A const& x) : a(x.a) {std::cout << "copy\n";}

    A inc() const { return A{a+1}; }

    int value() const { return a; }
};

std::ostream& operator<<(std::ostream& s, A const& a) {
    return s << a.value();
}


std::tuple<A,A> get(int a, int b) {
    return std::make_tuple(A{a}, A{b});
}

std::tuple<A,A> inc_get(A const& a, A const& b) {
    return std::make_tuple(a.inc(), b.inc());
}

int main() {

    std::cout << " > tie example <\n";

    A a{10};
    A b{100};

    SHOW(a);
    SHOW(b);

    std::tie(a,b) = get(11,111);

    SHOW(a);
    SHOW(b);

    std::tie(a,b) = inc_get(a,b);

    SHOW(a);
    SHOW(b);
}
