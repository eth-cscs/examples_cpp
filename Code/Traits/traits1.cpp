#include <iostream>

/**
   Classes A and B are two user classes that implements a given interface.
 */
template <typename ValueType>
struct A {
    using value_type = ValueType;
    static constexpr bool has_separators = true;

    value_type value;

    A(value_type v) : value{v} {}

    static std::string left_separator() {return " (";}
    static std::string right_separator() {return ") ";}
};

struct B {

    using value_type = std::string;
    std::string value;
    static constexpr bool has_separators = false;

    B(std::string && v) : value{std::move(v)} {}
};

/**
   A traits class is a class template that contains informations on how to manipulate
   objects of the types for which the traits are meaningful.
 */
template <typename T>
struct my_traits {

    static constexpr bool has_separators = T::has_separators;
    using value_type = typename T::value_type;


    static value_type get_value(T const& f)
    {
        return f.value;
    }

    static std::string default_separator() {return " - ";}
};


namespace print_impl {
    template <typename Traits, typename ObjectType>
    typename std::enable_if<Traits::has_separators, std::string>::type
    get_left_separator(ObjectType const& o) {
        return o.left_separator();
    }

    template <typename Traits, typename ObjectType>
    typename std::enable_if<! Traits::has_separators, std::string>::type
    get_left_separator(ObjectType const&) {
        return Traits::default_separator();
    }

    template <typename Traits, typename ObjectType>
    typename std::enable_if<Traits::has_separators, std::string>::type
    get_right_separator(ObjectType const& o) {
        return o.right_separator();
    }

    template <typename Traits, typename ObjectType>
    typename std::enable_if<! Traits::has_separators, std::string>::type
    get_right_separator(ObjectType const&) {
        return Traits::default_separator();
    }
}// namespace print_impl

/**
   The print function will take a list of objects for which the traits are valid
   and print something accorgingly.
 */
void print( ) {
    std::cout << "." << std::endl;
}

template <typename First, typename... T>
void print(First const& f, T const&... v) {
    using traits = my_traits<First>;

    auto ls = print_impl::get_left_separator<traits>(f);
    auto rs = print_impl::get_right_separator<traits>(f);
    typename traits::value_type value = traits::get_value(f);

    std::cout << ls << value << rs;
    print(v...);
}


struct complex { // A third party class
    double re, im;

    complex(double re, double im)
        : re(re)
        , im(im)
    {}
};

template <>
struct my_traits<complex> {

    static constexpr bool has_separators = false;
    using value_type = complex;


    static value_type get_value(complex const& f)
    {
        return f;
    }

    static std::string default_separator() {return " $$ ";}
};

std::ostream& operator<<(std::ostream& s, complex const& c) {
    return s << "{" << c.re << " + i" << c.im << "}";
}


int main() {

    print(A<int>(2), B("ciao"), A<double>(3.1415926), B("this is it"), complex(1.41, 3.14));

}
