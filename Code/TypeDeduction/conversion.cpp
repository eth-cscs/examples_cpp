#include <iostream>
#include <stdint.h>

void f(int8_t a) {
    std::cout << (int)a << std::endl;
}

struct A {};

#define SHOW(x) std::cout << #x << ": " << x << "\n";

struct B {
    B(char c) {}

    operator A() {return A{};}

    template <typename X>
    operator X() = delete;
};

struct C {
    operator B() {return B{'a'};}
};

int main() {
    int16_t a = 16383;
    SHOW(sizeof(int16_t));
    SHOW(sizeof(int8_t));
    SHOW(sizeof(int));

    {
        unsigned char ch = 2345;
    }

    {
        unsigned char ch = 234;
    }
    f(a);         // no warning

    f((short)16383);
    f((1 << 16)-1);    // warning

    int i = (1<<16)-1;
    f(i);    // warning

    char c1 = 32, c2 = 33;
    B x{c1+c2};
    {
        A y = static_cast<B>(C{});
    }
    {
        // A y = C{};
    }

}
