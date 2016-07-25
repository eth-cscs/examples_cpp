#include <iostream>

// The mental model of templates that substitute text is ok in almost all cases.
// But in this example we can see that ADL does not apply in template instantiation!

namespace name {
    struct X {};
    void foo(X) { std::cout << "name::foo: ";}
}

void foo(name::X) { std::cout << "::foo: ";}


template <typename T, void (*F)(T)>
void bar(T x) {
    F(x);
    //foo(x); // This goes in ADL
    std::cout << "ADL does not apply\n";
};

int main() {
    //foo(name::X{}); // Regular ADL

    bar<name::X, foo>(name::X{}); // bar calls foo(name::X) but it works! No ADL is used
    //bar<name::X, name::foo>(name::X{});
}