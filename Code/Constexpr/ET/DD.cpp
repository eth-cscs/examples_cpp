template <typename T1>
struct expr_derivative<expr_derivative<T1>>{
    using value_t = expr_derivative<typename expr_derivative<T1>::value_t>;

    template <typename T>
    constexpr T operator()(T t_) const {
        return value_t()(t_);
    }
};
