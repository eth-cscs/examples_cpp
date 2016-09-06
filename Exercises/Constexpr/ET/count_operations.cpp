#include <iostream>
/**
   Compute at compile time the sums and multiplications required by the expression to be evaluated.
   see the main() at the end of the file
*/

//////ALGEBRA/////////////
struct p{
    constexpr p(){}
    template <typename T>
    constexpr T operator()(T t_) const
    {return t_;}
};
constexpr p x = p();

template <typename T1, typename T2>
struct expr_plus{
    template<typename T>
    constexpr T operator ()(T t_) const {
        return T1()(t_)+T2()(t_);
    }
};

template<typename T1, typename T2>
constexpr expr_plus<T1, T2> operator + (T1, T2) {
    return expr_plus<T1, T2>();
}

template <typename T1, typename T2>
struct expr_times{
    template<typename T>
    constexpr T operator ()(T t_) const {
        return T1()(t_)*T2()(t_);
    }
};

template<typename T1, typename T2>
constexpr expr_times<T1, T2> operator * (T1, T2) {
    return expr_times<T1, T2>();
}

//////DERIVATIVE//////////

template <typename Expr>
struct expr_derivative{

    using value_t = int;

    template <typename T>
    constexpr T operator()(T t_) const {
        return (T)0;
    }

};

template<typename T>
constexpr expr_derivative<T> D(T) { return expr_derivative<T>();}

template <>
struct expr_derivative<p>{
    using value_t=int;

    template <typename T>
    constexpr T operator()(T t_) const {
        return (T)1;
    }
};

template <typename T1, typename T2>
struct expr_derivative<expr_plus<T1, T2> >{

    using value_t = decltype(D(T1()) + D(T2()));

    template <typename T>
    constexpr T operator()(T t_) const {
        return value_t()(t_);
    }
};

template <typename T1, typename T2>
struct expr_derivative<expr_times<T1, T2> >{

    using value_t = decltype(T1()*D(T2()) + T2()*D(T1()));

    template <typename T>
    constexpr T operator()(T t_) const {
        return value_t()(t_);
    }
};

template <typename T1>
struct expr_derivative<expr_derivative<T1>>{
    using value_t = expr_derivative<typename expr_derivative<T1>::value_t>;

    template <typename T>
    constexpr T operator()(T t_) const {
        return value_t()(t_);
    }
};

////////MAIN//////////////
int main(int argc , char** argv){

    constexpr auto expr = D(D(D(x*x+x)));

    std::cout<<expr(5.)<<"\n";

    /* Modify the code above in order complete the following lines */
    static_assert(expr.sums() == /*???*/);
    static_assert(expr.mults() == /*???*/);
}
