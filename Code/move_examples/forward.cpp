#include "../show.h"

void bar(int& x) {x++;}
void bar(int&& x) {std::cout << "Nothing\n";};

template <typename T>
void foo(T&& x) {
    //bar(std::move(x));
    bar(std::forward<T>(x));
}

int main() {
    int i = 19;
    foo(i);
    SHOW(i);
    foo<int&>(i);
    SHOW(i);
    foo(42);
}
