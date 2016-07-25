#include "../show.h"

template <typename Func, typename T>
void foo(Func func, T a, T b) {
    SHOW(func(a,b));
};


int main() {
    {
        auto f = [](auto a, auto b) {return a+b;};
        SHOW(f(42, 3.1415926));
    }
    {
        auto f = [](auto &a, auto &b) { return a++ + b; };
        int x = 42;
        double y = 3.1415926;
        SHOW(f(x,y));
        SHOW(x);
    }
    {
        auto f = [](auto a, auto b) {return a+b;};
        foo(f, 3.14, 3.52);
        foo(f, 42, 32);
    }
}
