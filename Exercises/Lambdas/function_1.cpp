#include <functional>
#include <iostream>
#include <cassert>

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

float bar(int a, int b, int c) {
    return static_cast<float>(a-b+c);
}

int main() {
    std::function< ???? > f = [](int a,int b) {
        std::cout << "lambda ";
        return static_cast<float>(a+b);};

    assert(f(3,4) == (float)(3+4));

    // Re-targeting to standalone foo
    f = ????;

    assert(f(3,4) == (float)(3+4));

    // Re-targeting to functor A
    f = ????;

    assert(f(3,4) == (float)(3+4));

    using namespace std::placeholders;

    // Re-targeting to bar using bind (look at assert)
    f = std::bind(bar, ???? );

    assert(f(3,4) == (float)(3+4));
}
