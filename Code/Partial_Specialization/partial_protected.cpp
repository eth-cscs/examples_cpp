// -*- compile-command: "g++ -std=c++11 partial_protected.cpp -o partial_protected" -*-

#include <iostream>

/**
   Primary template declaration, which takes two arguments, one with a default value
 */
template <typename T, int X = T::value>
struct A;

template <typename T>
struct A<T, 0> {
    /**
       We assume the user does not specify the second template argument, or,
       if her does, the value should be equal to T::value
     */
    static_assert(T::value == 0, "You're trying to cheat!");
    static constexpr int value = 0;
};

template <typename T>
struct A<T, 1> {
    /**
       We assume the user does not specify the second template argument, or,
       if her does, the value should be equal to T::value
     */
    static_assert(T::value == 1, "You're trying to cheat!");
    static constexpr int value = 1;
};

template <typename T>
struct A<T, 2> {
    /**
       We assume the user does not specify the second template argument, or,
       if her does, the value should be equal to T::value
     */
    static_assert(T::value == 2, "You're trying to cheat!");
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
      The following would not compile now
    */
    // std::cout << A<B<2>,1>::value << std::endl;

}
