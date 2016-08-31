#include "../show.h"

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
    static void go(T& x, F f) {
        for (int i = 0; i < std::extent<T,0>::value; ++i) {
            for (int j = 0; j < std::extent<T,1>::value; ++j) {
                for (int k = 0; k < std::extent<T,2>::value; ++k) {
                    f(x[i][j][k]);
                }
            }
        }
    }
};

template <typename T>
void looping(T x) {
    do_loop<rank<T>::value>::go(x);
}

int main() {
    SHOW((rank<int[3][4]>::value));

    int x[3][5];
    int i=0;
    std::cout << std::extent<decltype(x), 0>::value << ", "
              << std::extent<decltype(x), 1>::value << "\n";

    do_loop<std::rank<decltype(x)>::value>::go(x,
                                               [&i](int& v) {
                                                   std::cout << i << " ";
                                                   i++;
                                               });
}
