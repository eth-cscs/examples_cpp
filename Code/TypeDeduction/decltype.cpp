#include <type_traits>

int* foo(float, double) {return nullptr;}


int main() {
    int x = 10;
    int const& y = x;

    static_assert(std::is_same<decltype(10), int>::value, "");

    static_assert(std::is_same<decltype(x), int>::value, "");

    static_assert(std::is_same<decltype(x+10), int>::value, "");

    static_assert(std::is_same<decltype((x)), int&>::value, "");

    static_assert(std::is_same<decltype((x+10)), int>::value, "");

    int* (*f)(float, double) = nullptr;
    static_assert(std::is_same<decltype(f), int*(*)(float, double)>::value, "");

    static_assert(std::is_same<decltype(foo), int*(float, double)>::value, "");

    static_assert(std::is_same<decltype(foo(float{}, double{})), int*>::value, "");
    static_assert(std::is_same<decltype(f(float{}, double{})), int*>::value, "");

    int const* (*g)(float, double) = nullptr;
    static_assert(std::is_same<decltype(g), int const*(*)(float, double)>::value, "");
    static_assert(std::is_same<decltype(g(float{}, double{})), int const*>::value, "");

}
