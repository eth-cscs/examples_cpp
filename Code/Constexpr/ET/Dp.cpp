template <>
struct expr_derivative<p>{
    using value_t=int;
    template <typename T>
    constexpr T operator()(T t_) const {
        return (T) 1;
    }
};
