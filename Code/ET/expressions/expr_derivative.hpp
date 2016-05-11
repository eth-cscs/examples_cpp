#pragma once

namespace expressions{

    template <typename ArgType1>
    constexpr expr_derivative<ArgType1>
    D (ArgType1 arg1){
        return expr_derivative<ArgType1>();}

}//namespace expressions

template <typename ArgType1>
struct expr_derivative;

template<>
struct expr_derivative<p>{

    template <typename T>
    constexpr auto operator() (T t_) const{
        return (T) 1;
    }

    std::string to_string() const {
        return std::string(" D(") + p().to_string() + ") ";
    }
};

template <typename T1, typename T2>
struct expr_derivative<expr_plus<T1, T2> >{

    template <typename T>
    constexpr auto operator() (T t_) const{
        return expressions::D(T1())(t_)+expressions::D(T2())(t_);
    }

    std::string to_string() const {
        return std::string(" D(") + expr_plus<T1,T2>().to_string() + ") ";
    }
};

template <typename T1, typename T2>
struct expr_derivative<expr_times<T1, T2> >{

    template <typename T>
    constexpr auto operator()(T t_)  const{
        return
            T1()(t_) * expressions::D(T2())(t_)
            +
            expressions::D(T1())(t_) * T2()(t_);
    }
    std::string to_string() const {
        return std::string(" D(") + expr_times<T1,T2>().to_string() + ") ";
    }

};
