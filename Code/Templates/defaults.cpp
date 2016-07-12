#include "../show.h"

template <typename T, typename Return=char>
Return foo(T x) {
    return static_cast<Return>(x);
}

template <typename T=double, int size=10>
class my_container {};

int main() {

    // For functions:
    SHOW(foo(65));
    SHOW((foo<int, int>(65)))

    // For classes
    my_container<> x; // a my_container of doubles
                      // <>  are needed since my_container is a template!
}