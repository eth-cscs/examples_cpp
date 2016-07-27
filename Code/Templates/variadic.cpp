#include <tuple>
#include <vector>
#include "../show.h"

template <typename ...T>
struct A {
    static constexpr int count = sizeof...(T);
};

template <typename ...T>
struct B {
    using tuple = std::tuple<T...>;
    using tuple_of_vector = std::tuple<std::vector<T>...>;
};


int main() {
    SHOW((A<int, float>::count));

    using theB = B<int, char, float>;
    static_assert(std::is_same<std::tuple_element<0, theB::tuple_of_vector>::type, std::vector<int>>::value, "");
    static_assert(std::is_same<std::tuple_element<1, theB::tuple_of_vector>::type, std::vector<char>>::value, "");
}
