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
