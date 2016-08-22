#include "../show.h"
#include <tuple>
#include <string>

struct A {
    int &x;
    A(int &x) : x(x) {}

    int& get() { return x;}

    float value() const {return x;};
};

struct B {
    int x;
    B(int x) : x(x) {}

    int get() { return x;}

    char value() const {return x;};
};

void test() {
    int x=10;
    A a(x);
    B b(x);

    {
        SHOW(a.x);
        auto y = a.get();
        y += 1;
        SHOW(a.x);

        SHOW(a.x);
        decltype(auto) z = a.get();
        z += 1;
        SHOW(a.x);
    }

    {
        SHOW(b.x);
        auto y = b.get();
        y += 1;
        SHOW(b.x);

        SHOW(b.x);
        decltype(auto) z = b.get();
        z += 1;
        SHOW(b.x);
    }
}


template <typename F>
auto foo(F x)
    -> decltype(x.get()) // only C++11
{
    return x.get();
}

template <typename F>
decltype(auto) bar(F x) {
    return x.get();
}


int main() {
    test();

    std::tuple<int, float, char, std::string> t1{42, 3.14, 'z', std::string{"hello"}};
    auto t2 = std::make_tuple(42, 3.14f, 'z', std::string{"hello"});

    int x = 10;

    SHOW(inc(A(x)));
    //SHOW(inc(B(x)));

    SHOW(foo(A(x)));
    SHOW(foo(B(x)));

    SHOW(bar(A(x)));
    decltype(auto) x1 = bar(A(x));
    x1++;
    SHOW(bar(A(x)));

    SHOW(bar(B(x)));
    decltype(auto) x2 = bar(B(x));
    x2++;
    SHOW(bar(B(x)));
}
