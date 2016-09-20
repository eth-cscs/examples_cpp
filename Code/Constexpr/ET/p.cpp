struct p{
    constexpr p(){}
    template <typename T>
    constexpr T operator()(T t_) const
    {return t_;}
};
constexpr p x = p();
