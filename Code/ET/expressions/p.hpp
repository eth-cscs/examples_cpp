#pragma once

template<typename T>
struct p{
    const T value;

    constexpr p(T value_) : value{value_}{};

    static char const constexpr val[]=" p ";
    std::string to_string() const {

        return std::string(" p ");
    }
};

template <typename T>
constexpr p<T> arg(T const& t){
    return p<T>{t};
}

template <typename  T>
char const constexpr p<T>::val[];

namespace expressions{

    namespace evaluation{

        template <typename T>
        auto static constexpr value(p<T> const& arg)
        {
            return arg.value;
        }

        //automatic differentiation
        template <typename  T>
        auto static constexpr value(expr_derivative<p<T> > const& arg)
        {
            return (T)1.;
        }
    }
}
