#include "../show.h"

void bar(int& x) {x++;}
void bar(int&& x) {std::cout << "Nothing\n";};

template <typename T>
void foo(T&& x) {
    //bar(std::move(x));
    bar(std::forward<T>(x));
}

template <typename T>
void foo1(T x) {
    //bar(std::move(x));
    bar(std::forward<T>(x));
}

// void foo(int&);
// void foo(int&);

int test() {
    int i = 19;
    foo(i);
    SHOW(i);
    foo<int&>(i);
    SHOW(i);
    foo(42);
}

int test1() {
    int i = 19;
    foo1(i);
    SHOW(i);
    foo1<int&>(i);
    SHOW(i);
    foo1(42);
}

int main() {
    test();
    test1();
}
