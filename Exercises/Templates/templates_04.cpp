#ifdef NDEBUG
#undef NDEBUG
#endif

#include <iostream>
#include <cassert>

/** This is an exercise for VARIADIC TEMPLATES */

namespace max_size_of {
    /** takes a list of types and determines the maximum sizeof */
    template <typename ????>
    struct max_size_of;

    template <typename First, typename ????>
    struct max_size_of< ???? > {
        static const unsigned size_of_rest = max_size_of< ???? >::value;
        static const unsigned value = sizeof(First) > size_of_rest?sizeof(First):size_of_rest;
    };

    template <>
    struct max_size_of<> {
        static const unsigned value = 0;
    };
} // namespace max_size_of

namespace max_type_of {
    /** helper function to implement a kind of ternary operator on types */
    template <bool SelectFirst, typename T, typename U>
    struct select_first {
        using type = T;
    };

    template <typename T, typename U>
    struct select_first<false, T, U> {
        using type = U;
    };

    /** Given a list of types it provide the type with the maximum size */
    template < ???? >
    struct max_type_of;

    template <typename First, typename ???? >
    struct max_type_of< ???? > {
        using type = typename select_first<(sizeof(First) > sizeof(typename max_type_of< ???? >::type)),
            First, typename max_type_of< ???? >::type
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
