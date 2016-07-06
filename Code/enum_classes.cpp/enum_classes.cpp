#include <iostream>
#include <typeinfo>
#include "../show.h"

enum class Color : char {Red = 'r', Green = 'g', Blue = 'b'};

enum Size {Small=-1, Medium, Large};
enum Car {Sedan, Coupe, Compact};

std::ostream& operator<<(std::ostream& s, Color c) {
    return s << static_cast<char>(c);
}


template <Color C>
void foo() {
    std::cout << "Color " << C << "\n";
}


int main() {
    foo<Color::Red>();
    foo<Color::Green>();
    foo<Color::Blue>();
    //foo<1>(); // Error: no conversion from int to Color
    foo<static_cast<Color>(65)>(); // ?? UB?

    SHOW_BOOL((std::is_same<std::underlying_type<Color>::type, char>::value));
    SHOW_BOOL((std::is_same<std::underlying_type<Color>::type, int>::value));

    SHOW_BOOL((std::is_same<std::underlying_type<Car>::type, unsigned int>::value));
    SHOW_BOOL((std::is_same<std::underlying_type<Car>::type, int>::value));

    SHOW_BOOL((std::is_same<std::underlying_type<Size>::type, unsigned int>::value));
    SHOW_BOOL((std::is_same<std::underlying_type<Size>::type, int>::value));

    // Color x{1}; Since C++17
}
