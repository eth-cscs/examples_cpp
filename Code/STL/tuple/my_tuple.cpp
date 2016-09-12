template<typename ... T> struct my_tuple;

template<typename First, typename ... T>
struct my_tuple<First, T...> : public my_tuple<T ...> {
    using super=my_tuple<T ...>;
    static constexpr int size = sizeof...(T)+1;

    constexpr my_tuple(First first_, T ... rest_) : super(rest_ ...), m_value(first_){}

    First m_value;
};
