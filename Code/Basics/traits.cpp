#include <iostream>


template <typename ValueType>
struct A {
    using value_type = ValueType;

    value_type value;

    A(value_type v) : value(v) {}
};

struct B {

    std::string value;

    B(std::string && v) : value(std::move(v)) {}
};

template <typename T>
struct my_traits {

    template <typename U>
    static std::string my_to_string(U const& v) { return std::to_string(v); }
    static std::string my_to_string(std::string const& v) { return v; }

    static std::string left_separator() {return " (";}
    static std::string right_separator() {return ") ";}
    static constexpr std::string get_value(T const& f)
    {
        return my_to_string(f.value);
    }
};

void print( ) {
    std::cout << "." << std::endl;
}

template <typename First, typename... T>
void print(First const& f, T const&... v) {
    using traits = my_traits<First>;

    std::cout << traits::left_separator() << traits::get_value(f) << traits::right_separator();
    print(v...);
}


int main() {

    print(A<int>(2), B("ciao"), A<double>(3.1415926), B("this is it"));

    return 0;
}
