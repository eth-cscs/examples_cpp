#include <iostream>

template <unsigned char N>
struct factorial {
    static constexpr unsigned value = N * factorial<N-1>::value;
};

template <>
struct factorial<1> {
    static constexpr unsigned value=1;
};


int main() {
    std::cout << factorial<5>::value << "\n";
}