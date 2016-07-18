
#include <iostream>

template <unsigned char N, typename Pred = void>
struct factorial;

template <unsigned char N>
struct factorial<N, typename std::enable_if<N<=12, void>::type> {

    static constexpr unsigned value = N * factorial<N-1>::value;
};

/* alternative solution with just a statis assert
 * in this case the second template argument is not needed
template <unsigned char N>
struct factorial<N, void> {
    static_assert(N<=12, "The argument to factorial is too big");
    static constexpr unsigned value = N * factorial<N-1>::value;
};
*/

template <>
struct factorial<1, void> {
    static constexpr unsigned value=1;
};

template <unsigned char N>
struct factorial<N, typename std::enable_if<(N>12), void>::type> {
    // commenting out for sake of compilation static_assert(false, "The argument to factorial is too big");
    static constexpr unsigned value = 0;
};

int main() {
    std::cout << factorial<5>::value << "\n";
    std::cout << factorial<12>::value << "\n";
    std::cout << factorial<13>::value << "\n";
}

