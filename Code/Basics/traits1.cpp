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
    static std::string get_value(T const& f)
    {
        return my_to_string(f.value);
    }
};

/**
   This is a third party class thatwe want to use with our
   print function. We can then define a specialization of the trairs.
 */
template <bool UseCurly=true>
struct C {

    using use_curly = UseCurly;

    struct complex_t {
        float a;
        float b;
    };

    /* If c_value was called value, then the primary template
       my_traits could have been used if the to_string function
       was defined. But std::to_string cannod be specialized for
       user types in the namespace std. A using statement may solve
       this but I would not judge that clean. */

    complex_t c_value;

    C(float a, float b) : c_value{a,b} {}
};

/**
   This is a specialization of the traits for the new class C
   that comes from some other software.
 */
template <bool UseCurl>
struct my_traits<C<UseCurl>> {

    static std::string left_separator() {return UseCurl?" {":" (";}
    static std::string right_separator() {return UseCurl?"} ":") ";}
    static std::string get_value(C<UseCurl> const& f)
    {
        return std::to_string(f.c_value.a) + " + i" + std::to_string(f.c_value.b);
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

    print(A<int>(2), B("ciao"), A<double>(3.1415926), B("this is it"), C<>(1.2, 3.4),  C<false>(1.2, 3.4) );

    return 0;
}
