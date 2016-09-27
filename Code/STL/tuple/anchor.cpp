template<typename ... T> struct my_tuple;

template<typename First>
struct my_tuple<First> {
    constexpr my_tuple(First first_) : m_value(first_){}
    template<int Id> constexpr First get(){return m_value;}
    First m_value;
};
