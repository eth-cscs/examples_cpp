#include <iostream>

template<typename ... T> struct my_tuple;

template<typename First>
struct my_tuple<First> {
    static constexpr int size=1;
    constexpr my_tuple(First first_) : m_value(first_){}
    template<int Id> constexpr First get() const {return m_value;}
    First m_value;
};

template<typename First, typename ... T>
struct my_tuple<First, T...> : public my_tuple<T ...> {
    using super=my_tuple<T ...>;
    static constexpr int size = sizeof...(T);

    constexpr my_tuple(First first_, T ... rest_) : super(rest_ ...), m_value(first_){}

    First m_value;

    template<int Id>
    constexpr auto get() const {return Id==size ? m_value : super::template get<Id>();}

};

template<int Id, typename Tuple>
constexpr auto get(Tuple t_){ return t_.template get<Tuple::size-Id>();}


int main(){
    constexpr my_tuple<int, double> t_(1,3.4);
    std::cout<<get<1>(t_)<<"\n";
    static_assert(get<1>(t_)==3.4, "");
}
