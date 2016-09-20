
template <typename T1, typename T2>
struct expr_derivative<expr_plus<T1, T2> >{

    using value_t = decltype(D(T1()) + D(T2()));

    template <typename T>
    constexpr T operator()(T t_) const {
        return value_t()(t_);
    }
};
