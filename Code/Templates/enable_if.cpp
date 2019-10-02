#include <utility>
#include <type_traits>
#include "../show.h"


namespace V1 {
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
} // namespace V1

namespace V2 {
    template <typename T, typename VOID = void>
    struct A;

    template <typename T>
    struct A<T, std::enable_if_t<std::is_same_v<T, int>, void>> {
        A() { std::cout << "int!\n"; }
    };


    template <typename T>
    struct A<T, std::enable_if_t<!std::is_same_v<T, int>, void>> {
        A() { std::cout << "not int\n"; }
    };
} // namespace V2

int main() {
    {
        V1::A<int> x;
        V1::A<float> y;
    }
    {
        V2::A<int> x;
        V2::A<float> y;
    }
}
