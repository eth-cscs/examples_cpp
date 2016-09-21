template <>
struct expr_derivative<p>{

    template <typename T>
    constexpr T operator()(T t_) const {
        return (T) 1;
    }
};
