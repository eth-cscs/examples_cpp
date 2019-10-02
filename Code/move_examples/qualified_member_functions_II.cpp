#include <iostream>
#include <type_traits>

struct A {
    int a;

    A(int a) : a{a} {}

    int foo(int i) & noexcept {
        a += i;
        return i;
    }

    int foo(int i) const& noexcept {
        std::cout << "\nwarning: no udate (const&)!\n";
        return i;
    }

    // could be commented out
    int foo(int i) &&  noexcept {
        std::cout << "\nwarning: no udate (&&)!\n";
        return i;
    }

    int operator[](int i) & noexcept {
        a += i;
        return a;
    }

    int operator[](int i) const& noexcept {
        std::cout << "\nno update (const&)\n";
        return a+i;
    }

    // could be commented out
    int operator[](int i) && noexcept {
        std::cout << "\nno update (&&)\n";
        return a+i;
    }
};

template <typename T, typename U>
int bar(T&& a, U&& b) {
    return std::forward<T>(a).foo(10) + std::forward<U>(b).foo(10);
}

template <typename T, typename U>
int zig(T&& a, U&& b) {

    return std::forward<T>(a)[0] + std::forward<U>(b)[10];
}


int moo(A const & a, A const& b) {
    return bar(a,b);
}

#define show(x) std::cout << #x << ": " << x << std::endl;

int main() {
    A a = 50;
    int x = a.foo(10);

    A b = 30;

    show(bar(a,b));

    show(bar(a, A{40}));

    show(moo(a,b));
    show(moo(a,A{40}));


    show(zig(a,b));
    show(zig(a, A{66}));
}
