// -*- compile-command: "g++ -std=c++11 partial.cpp -o partial" -*-

#include <iostream>

/**
   Primary template declaration, which takes two arguments, one with a default value
 */
template <typename T, int X = T::value>
struct A;

template <typename T>
struct A<T, 0> {
    static constexpr int value = 0;
};

template <typename T>
struct A<T, 1> {
    static constexpr int value = 1;
};

template <typename T>
struct A<T, 2> {
    static constexpr int value = 2;
};

template <int Value>
struct B {
    static constexpr int value = Value;
};

int main() {

    /**
       When specifying A with a single template argument the primary templare is searched to
       see if the code instantiation is comformant with the declaration.
       In this case, only one argument is provided, so the second is taken from the default,
       so that A<B<2>> becomes A<B<2>, 2>, from which the partial specialization is then
       selected.
     */
    std::cout << A<B<2>>::value << std::endl;

    /**
      The following compiles and returns 1. Can this be prevented? See partial_protected.cpp
    */
    std::cout << A<B<2>,1>::value << std::endl;

}
