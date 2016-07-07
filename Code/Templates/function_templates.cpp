#include <iostream>

template <typename T>
void foo(T x) {
    std::cout << x << "\n";
}

void foo(std::string const& x) {
    std::cout << "ooh! a string! " << x << "\n";
}

int main() {
    foo<int>(65);
    foo<char>(65);

    // Template arguments types are deduced!
    foo(3.14159);

    foo(std::string("string"));
}
