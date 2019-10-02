#include <iostream>
#include <typeinfo>
#include <algorithm>
#include "../show.h"

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

A operator+(A const& a ,A const& b) {
    return A(a.m + b.m);
}

void foo(A const& x) {
    std::cout << "A & " << x.m << std::endl;
}

void foo(A && x) {
    std::cout << "A && " << x.m << std::endl;
}

struct X {
    template <typename T>
    void push_back(T&& x) {
        std::cout << "rvalue " << x << "\n";
    }

    template <typename T>
    void push_back(T const& x) {
        std::cout << "lvalue " << x << "\n";
    }
};

template <typename T>
struct Y {
    void push_back(T&& x) {
        std::cout << "rvalue " << x << "\n";
    }

    void push_back(T const& x) {
        std::cout << "lvalue " << x << "\n";
    }
};


int main() {

    {
        int i;
        SHOW((&i));
        int && a = 10;
        SHOW((&a));
        auto && b = a;
        SHOW((&b));
        SHOW_BOOL((std::is_same<decltype(b), int&>::value));
    }
    {
        int && a = 10;
        SHOW((&a));
        auto & b = a;
        SHOW((&b));
        SHOW_BOOL((std::is_same<decltype(b), int&>::value));
    }
    {
        int && a = 10;
        SHOW((&a));
        auto b = a;
        SHOW((&b));
        SHOW_BOOL((std::is_same<decltype(b), int>::value));
    }
    {
        int && b = 10;
        SHOW((&b));
        SHOW_BOOL((std::is_same<decltype(b), int&&>::value));
    }
    {
        int && a = 10;
        SHOW((&a));
        auto && b = std::move(a);
        SHOW((&b));
        b = 20;
        SHOW_BOOL((std::is_same<decltype(b), int&&>::value));
    }
    {
        int && a = 10;
        SHOW((&a));
        auto && b = std::forward<int&&>(a);
        SHOW((&b));
        SHOW_BOOL((std::is_same<decltype(b), int&&>::value));
    }
    {
        auto && b = 10;
        SHOW((&b));
        SHOW_BOOL((std::is_same<decltype(b), int&&>::value));
    }

    {
        A a(10), b(20);

        std::cout << ((a + b).m) << std::endl;


        A &&ar = std::move(a);

        ar.m = 14;

        std::cout << a.m << " == " << ar.m << std::endl;

        foo(a);
        foo(ar);
        foo(std::move(ar));
    }
    {
        X x;
        x.push_back(3);
        int i = 7;
        x.push_back(i);
        const int& j = i;
        x.push_back(j);
    }
    {
        Y<int> x;
        x.push_back(3);
        int i = 7;
        x.push_back(i);
        const int& j = i;
        x.push_back(j);
    }
}
