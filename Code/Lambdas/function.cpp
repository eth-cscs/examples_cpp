#include <functional>
#include "../show.h"

float foo(int a, int b) {
    std::cout << "stand alone ";
    return static_cast<float>(a+b);
}

struct A {
    float operator()(int a, int b) {
        std::cout << "functor ";
        return static_cast<float>(a+b);
    }
};

int main() {
    std::function<float(int,int)> f = [](int a,int b) {
        std::cout << "lambda ";
        return static_cast<float>(a+b);};

    SHOW(f(3,4));

    // Re-targeting to standalone
    f = foo;
    SHOW(f(3,4));

    // Re-targeting to functor
    f = A();
    SHOW(f(3,4));

    using namespace std::placeholders;

    f = std::bind([](int a, int b, int c) { std::cout << "binded "; return a+b-c;},
                  _1, _2, 0);
    SHOW(f(3,4));
}

