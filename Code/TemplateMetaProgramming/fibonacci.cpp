#include <iostream>

template <unsigned char N>
struct fibonacci {
    static constexpr unsigned value = fibonacci<N-1>::value + fibonacci<N-2>::value;
};

template <>
struct fibonacci<1> {
    static constexpr unsigned value = 1;
};

template <>
struct fibonacci<0> {
    static constexpr unsigned value = 0;
};

int main() {
    std::cout << fibonacci<6>::value << "\n";  //  movl    $8, %esi
}
