template <typename T>
struct expr_derivative{
    using value_t = int;

    template <typename T>
    constexpr T operator()(T t_) const {
        return 0;
    }
};

template<typename T>
constexpr expr_derivative<T> D(T) { return expr_derivative<T>();}
