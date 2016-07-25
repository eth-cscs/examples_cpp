#include <string>

template <typename T, typename U>
void foo(T, U) {
    static_assert(std::is_same<U, double>::value, "");
}

// Template arguments are evaluated left to right. The following line is wrong
//template <typename T, int X = U::value, typename U = typename T::type>
template <typename T, typename U = typename T::type, int X = U::value>
struct Order {};

struct B {
    using type = B;
    static const int value = 100;
};

int main() {
    foo<std::string, double>("hello", 4.5); // Ok!
    foo<std::string>("hello", 4.5); // Ok!
    //foo<double>("hello", 4.5); // Error!

    Order<B> x;
}
