
#include "../show.h"

struct A {
    void foo(int, int) {}
};

struct B {};

template <typename T>
using void_t = void;

template <typename T, typename VOID = void>
struct has_foo {
    static constexpr bool value = false;
};

template <typename T>
struct has_foo<T, void_t<decltype(T{}.foo(int{}, int{}))> > {
    static constexpr bool value = true;
};

int main() {
    SHOW_BOOL((has_foo<A>::value));
    SHOW_BOOL((has_foo<B>::value));
}
