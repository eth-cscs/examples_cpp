#include <utility>
#include <type_traits>
#include "../show.h"

template <typename T, typename VOID = void>
struct A;

template <typename T>
struct A<T, typename std::enable_if<std::is_same<T, int>::value, void>::type> {
    A() { std::cout << "int!\n"; }
};


template <typename T>
struct A<T, typename std::enable_if<!std::is_same<T, int>::value, void>::type> {
    A() { std::cout << "not int\n"; }
};

int main() {
    A<int> x;
    A<float> y;
}
