template<bool Cond>
struct constexpr_if;

template<>
struct constexpr_if<true>{
    template <typename Left, typename Right>
    static constexpr Left apply(Left l_, Right r_)
    {return l_;}
};

template<>
struct constexpr_if<false>{
    template <typename Left, typename Right>
    static constexpr Right apply(Left l_, Right r_)
    {return r_;}
};
