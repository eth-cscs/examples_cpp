#pragma once

namespace expressions{

    template <typename T1>
    struct expr_derivative;

    template <typename T1>
    constexpr auto
    D (T1 arg1){
        return expr_derivative<T1>(arg1);
    }

template <typename T1>
struct expr_derivative<expr_derivative<T1>>{

    expr_derivative<T1> arg1;

    constexpr expr_derivative(expr_derivative<T1> arg) : arg1{arg} {}

    template <typename T>
    constexpr auto operator() (T t_) const{
        return expr_derivative<expr_derivative<T1>>(arg1.arg1)(t_);
    }

    std::string to_string() const {
        return D(D(arg1.arg1)).to_string();
    }

    //solution exercice 1
    constexpr int sum_ops() const {
        return D(D(arg1.arg1)).sum_ops();
    }
    constexpr int mult_ops() const {
        return D(D(arg1.arg1)).mult_ops();
    }
    //////////////////////
};


template <>
struct expr_derivative<expr_derivative<p> >{

    constexpr expr_derivative(p) {}

    template <typename T>
    constexpr T operator()(T t_) const {
        return 0;
    }

    std::string to_string() const {
        return std::string(" 0 ");
    }

    //solution exercice 1
    constexpr int sum_ops() const {
        return 0;
    }
    constexpr int mult_ops() const {
        return 0;
    }
    //////////////////////
};


template<>
struct expr_derivative<p>{

    constexpr expr_derivative(p) {}

    template <typename T>
    constexpr auto operator() (T t_) const{
        return (T)1;
    }

    std::string to_string() const {
        return std::string(" 1 ");
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

template<typename U>
struct expr_derivative<c<U>>{
    c<U> arg1;

    constexpr expr_derivative(c<U> x) : arg1{x} {}

    template <typename T>
    constexpr auto operator() (T t_) const{
        return 0;
    }

    std::string to_string() const {
        return std::string(" 0 ");
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

    expr_plus<T1, T2> arg1;

    constexpr expr_derivative(expr_plus<T1,T2> arg) :arg1(arg) {}

    template <typename T>
    constexpr auto operator() (T t_) const{
        return D(arg1.arg1)(t_) + D(arg1.arg2)(t_);
    }

    std::string to_string() const {
        return D(arg1.arg1).to_string() + " + " + D(arg1.arg2).to_string();
    }

    //solution exercice 1
    constexpr int sum_ops() const {
        return 1 + arg1.arg1.sum_ops() + arg1.arg2.sum_ops();
    }
    constexpr int mult_ops() const {
        return 0 + arg1.arg1.mult_ops() + arg1.arg2.mult_ops();
    }
    ////////////////////
};

template <typename T1, typename T2>
struct expr_derivative<expr_times<T1, T2> >{

    expr_times<T1, T2> arg1;

    constexpr expr_derivative(expr_times<T1,T2> arg1) :arg1(arg1) {}

    template <typename T>
    constexpr auto operator()(T t_)  const{
        return arg1.arg1(t_) * D(arg1.arg2)(t_) + D(arg1.arg1)(t_) * arg1.arg2(t_);
    }

    std::string to_string() const {
        return arg1.arg1.to_string() + " * " + D(arg1.arg2).to_string() + " + " +  D(arg1.arg1).to_string() + " * " + arg1.arg2.to_string();
    }

    //solution exercice 1
    constexpr int sum_ops() const {
        return 1 + arg1.arg1.sum_ops() + D(arg1.arg2).sum_ops() + D(arg1.arg1).sum_ops() + arg1.arg2.sum_ops();
    }
    constexpr int mult_ops() const {
        return 2 + arg1.arg1.mult_ops() +  D(arg1.arg2).mult_ops() + D(arg1.arg1).mult_ops() + arg1.arg2.mult_ops();
    }
    /////////////////////
};


}//namespace expressions

// template <typename T>
// auto constexpr const expr_derivative<T>::value;
