#include "../show.h"
#include <cxxabi.h>
#include <memory>
#include <typeinfo>

std::shared_ptr<char> cppDemangle(const char *abiName)
{
    int status;
    char *ret = abi::__cxa_demangle(abiName, 0, 0, &status);

    /* NOTE: must free() the returned char when done with it! */
    std::shared_ptr<char> retval;
    retval.reset( (char *)ret, [](char *mem) { if (mem) free((void*)mem); } );
    return retval;
}

template<class T, T v>
struct integral_constant {
    typedef T value_type;
    static constexpr value_type value = v;
};


template <typename T>
struct rank {
    static constexpr int value = 0;
};

template <typename T, int N>
struct rank<T[N]> {
    static constexpr int value = 1 + rank<T>::value;
};

template <typename T>
struct rank<T[]> {
    static constexpr int value = 1 + rank<T>::value;
};

namespace _detail {
    template <typename T>
    struct array_is_complete_array {
        static constexpr bool value = true; // starting point
    };

    template <typename T, int N>
    struct array_is_complete_array<T[N]> {
        static constexpr bool value = true and array_is_complete_array<T>::value;
    };

    template <typename T>
    struct array_is_complete_array<T[]> {
        static constexpr bool value = false and array_is_complete_array<T>::value;
    };

    template <typename T>
    struct array_is_complete_array<T*> {
        static constexpr bool value = false and array_is_complete_array<T>::value;
    };

} // namespace detail

template <typename T>
struct is_complete_array {
    static const bool value = std::is_array<T>::value and _detail::array_is_complete_array<T>::value;
};

template <int Dims>
struct do_loop;

template <>
struct do_loop<2> {
    template <typename T, typename F>
    static void go(T& x, F f) {

        std::cout << rank<T>::value << " "
                  << std::extent<T, 0>::value << ", "
                  << std::extent<T, 1>::value << "\n";
        for (int i = 0; i < std::extent<T, 0>::value; ++i) {
            for (int j = 0; j < std::extent<T,1>::value; ++j) {
                    f(x[i][j]);
            }
        }
    }
};

template <>
struct do_loop<3> {
    template <typename T, typename F>
    static void go(T& x, F&& f) {
        for (int i = 0; i < std::extent<T,0>::value; ++i) {
            for (int j = 0; j < std::extent<T,1>::value; ++j) {
                for (int k = 0; k < std::extent<T,2>::value; ++k) {
                    f(x[i][j][k]);
                }
            }
        }
    }
};

template <typename T, typename F>
void looping(T& x, F&& f) {
    static_assert(std::is_array<T>::value, "The data passed to looping must be a complete array type: T is not an array");
    static_assert(is_complete_array<T>::value, "The data passed to looping must be a complete array type: T is an aryray but it is not a complete array");
    SHOW_BOOL((is_complete_array<T>::value));
    do_loop<rank<T>::value>::go(x, std::forward<F>(f));
}

class A {};

template <typename T>
void bar(T (&x)[3][5]) {
    looping(x, [](int& v) { });
}

template <typename T>
void foo(T x[][5]) {
    looping(x, [](int& v) { });
    std::cout << cppDemangle(typeid(x).name()) << "*****************\n";
}

int main() {
    SHOW((std::rank<int[3][5]>::value));
    SHOW_BOOL((std::is_array<int[][4]>::value));
    SHOW_BOOL((is_complete_array<int[][4]>::value));

    SHOW_BOOL((std::is_array<int*[4]>::value));
    SHOW_BOOL((is_complete_array<int*[4]>::value));

    int x[][5] = { {1,2,3}, {2,3,4}, {3,4,5}};

    bar(x);
    //foo(x);
    std::cout << cppDemangle(typeid(x).name()) << "\n";

    int i=0;
    std::cout << std::extent<decltype(x), 0>::value << ", "
              << std::extent<decltype(x), 1>::value << "\n";

    A a{};
    looping(x, [&i](int& v) {
            std::cout << i << " ";
            i++;
        });

    int (*b)[5] = new int[3][5];
    std::cout << cppDemangle(typeid(b).name()) << "\n";
    looping(x, [&i](int& v) {
            std::cout << i << " ";
            i++;
        });
}
