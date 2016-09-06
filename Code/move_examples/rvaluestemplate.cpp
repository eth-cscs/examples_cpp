#include <type_traits>
#include <iostream>

template <typename T>
void foo(T&& x) {
    if (std::is_same<decltype(x), int&>::value) {
        std::cout << "T&\n";
    } else
    if (std::is_same<decltype(x), int&&>::value) {
        std::cout << "T&&\n";
    } else {
        std::cout << "Something else\n";
    }
}

int main() {
    int i = 19;
    foo(i);
    foo<int&>(i);
    foo(42);
}
