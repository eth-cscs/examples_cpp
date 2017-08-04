#ifdef NDEBUG
#undef NDEBUG
#endif

#include <iostream>
#include <cassert>
#include "../show.h"


namespace max_size_of {
    template <typename ...Ts>
    struct max_size_of;

    template <typename First, typename ...Rest>
    struct max_size_of<First, Rest...> {
        static const unsigned size_of_rest = max_size_of<Rest...>::value;
        static const unsigned value = sizeof(First) > size_of_rest?sizeof(First):size_of_rest;
    };

    template <>
    struct max_size_of<> {
        static const unsigned value = 0;
    };
} // namespace max_size_of

namespace max_type_of {
    template <bool SelectFirst, typename T, typename U>
    struct select_first {
        using type = T;
    };

    template <typename T, typename U>
    struct select_first<false, T, U> {
        using type = U;
    };

    template <typename ...Ts>
    struct max_type_of;

    template <typename First, typename ...Rest>
    struct max_type_of<First, Rest...> {
        using type = typename select_first<(sizeof(First) > sizeof(typename max_type_of<Rest...>::type)),
            First, typename max_type_of<Rest...>::type
            >::type;
    };

    template <typename First>
    struct max_type_of<First> {
        using type = First;
    };
} // namespace max_type_of


int main() {
    std::cout << " > Templates_04 <\n";
    assert((max_size_of::max_size_of<int, char, double, float>::value) == sizeof(double));
    static_assert(std::is_same<max_type_of::max_type_of<int, char, double, float>::type, double>::value, "");
    assert((std::is_same<max_type_of::max_type_of<int, char, double, float>::type, double>::value));
}
