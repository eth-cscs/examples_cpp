#pragma once

namespace expressions{

    template <typename T1>
    struct expr_derivative;

template <typename T1>
struct expr_derivative<expr_derivative<T1>>{

    using value_t = decltype(D(D(T1())));

    template <typename T>
    constexpr auto operator() (T t_) const{
        return value_t()(t_);
    }

    std::string to_string() const {
        return std::string(" D(") + T1().to_string() + ") ";
    }

    //solution exercice 1
    constexpr int sum_ops() const {
        return value_t().sum_ops();
    }
    constexpr int mult_ops() const {
        return value_t().mult_ops();
    }
    //////////////////////
};

template<>
struct expr_derivative<p>{

    using value_t = int;

    template <typename T>
    constexpr auto operator() (T t_) const{
        return (T) 1;
    }

    std::string to_string() const {
        return std::string(" D(") + p().to_string() + ") ";
    }

    //solution exercice 1
    constexpr int sum_ops() const {
        return 0;
    }
    constexpr int mult_ops() const {
        return 0;
    }
    /////////////////////
};

template <typename T1, typename T2>
struct expr_derivative<expr_plus<T1, T2> >{

    using value_t = decltype(D(T1())+ D(T2()));

    template <typename T>
    constexpr auto operator() (T t_) const{
        return value_t()(t_);
    }

    std::string to_string() const {
        return std::string(" D(") + expr_plus<T1,T2>().to_string() + ") ";
    }

    //solution exercice 1
    constexpr int sum_ops() const {
        return value_t().sum_ops();
    }
    constexpr int mult_ops() const {
        return value_t().mult_ops();
    }
    ////////////////////
};

template <typename T1, typename T2>
struct expr_derivative<expr_times<T1, T2> >{

    using value_t = decltype(T1() * D(T2())
                             +
                             D(T1()) * T2());

    template <typename T>
    constexpr auto operator()(T t_)  const{
        return value_t()(t_);
    }
    std::string to_string() const {
        return std::string(" D(") + expr_times<T1,T2>().to_string() + ") ";
    }

    //solution exercice 1
    constexpr int sum_ops() const {
        return value_t().sum_ops();
    }
    constexpr int mult_ops() const {
        return value_t().mult_ops();
    }
    /////////////////////
};

    template <typename T1>
    constexpr expr_derivative<T1>
    D (T1 arg1){
        return expr_derivative<T1>();}


}//namespace expressions

// template <typename T>
// auto constexpr const expr_derivative<T>::value;
