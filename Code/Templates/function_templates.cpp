#include <iostream>

template <typename T>
void foo(T x) {
    std::cout << x << "\n";
}

void foo(std::string const& x) {
    std::cout << "ooh! a string! " << x << "\n";
}

int main() {
    foo<int>(65); // Template argument is specified...
    foo<char>(65); // ... so this call passes a char ('A')

    // Template arguments types are deduced!
    foo(3.14159);

    foo(std::string("string")); // This goes to the free-standing function that takes a string which is more specialized

    foo<std::string>(std::string("another string")); // This goes to the template implementation of foo, since this syntax explicitly says that a template instantiation is required
}
