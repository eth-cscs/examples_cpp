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

namespace is_in {

    template <typename X, typename ...Us>
    struct is_in {

        template <int Index, typename T, typename ...Rest>
        struct is_in_impl;

        template <int Index, typename T, typename First, typename ...Rest>
        struct is_in_impl<Index, T, First, Rest...> {
            static const bool value = std::is_same<T, First>::value || is_in_impl<Index+1, T, Rest...>::value;
            static const int index = (std::is_same<T, First>::value)?Index:is_in_impl<Index+1, T, Rest...>::index;
        };

        template <int Index, typename T>
        struct is_in_impl<Index, T> {
            static const int index = -1;
            static const bool value = false;
        };

        static const bool value = is_in_impl<0, X, Us...>::value;
        static const int index = is_in_impl<0, X, Us...>::index;
    };
} // namespace is_in



template <typename ...Ts>
struct simple_variant {
    alignas(std::alignment_of<typename max_type_of::max_type_of<Ts...>::type>)
    char _store[max_size_of::max_size_of<Ts...>::value];
    int index = -1;

    template <typename T>
    constexpr bool contains() const {
        return is_in::is_in<T, Ts...>::value;
    }

    template <typename T>
    constexpr int index_of() const {
        return is_in::is_in<T, Ts...>::index;
    }

    template <typename T>
    typename std::enable_if<is_in::is_in<T, Ts...>::value, void>::type
    set_value(T v) {
        new (reinterpret_cast<void*>(_store)) T{v};
        index = is_in::is_in<T, Ts...>::index;
    }

    template <typename T>
    typename std::enable_if<is_in::is_in<T, Ts...>::value, T>::type
    get_value() {
        if (index != is_in::is_in<T, Ts...>::index) {
            throw(std::runtime_error("The requested type is not the one stored"));
        }
        return *(reinterpret_cast<T*>(_store));
    }

};

int main() {
    std::cout << "> templates_04 <\n";

    simple_variant<int, char, float, double> v;
    assert(sizeof(v)==sizeof(double)+sizeof(int));

    SHOW_BOOL((v.contains<float>()));
    SHOW((v.index_of<float>()));
    assert(v.index_of<float>()==2);

    SHOW_BOOL((v.contains<char>()));
    SHOW((v.index_of<char>()));
    assert(v.index_of<char>()==1);

    SHOW_BOOL((v.contains<int>()));
    SHOW((v.index_of<int>()));
    assert(v.index_of<int>()==0);

    SHOW_BOOL((v.contains<double>()));
    SHOW((v.index_of<double>()));
    assert(v.index_of<double>()==3);

    SHOW_BOOL((v.contains<long long>()));
    SHOW((v.index_of<long long>()));
    assert(v.index_of<long long>()==-1);

    DO((v.set_value<float>(3.14159f)));

    try {
        SHOW(v.get_value<float>());
        assert(v.get_value<float>() == 3.14159f);
    }
    catch (std::exception &e) {
        std::cout << "Excepiton: " << e.what() << "\n";
    }

    try {
        SHOW(v.get_value<int>());
    }
    catch (std::exception &e) {
        std::cout << "Excepiton: " << e.what() << "\n";
    }

    DO((v.set_value<int>(42)));

    try {
        SHOW(v.get_value<int>());
        assert(v.get_value<int>() == 42);
    }
    catch (std::exception &e) {
        std::cout << "Excepiton: " << e.what() << "\n";
    }

    try {
        SHOW(v.get_value<char>());
    }
    catch (std::exception &e) {
        std::cout << "Excepiton: " << e.what() << "\n";
    }



}
