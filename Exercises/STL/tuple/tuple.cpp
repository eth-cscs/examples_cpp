#include <iostream>
#include <string>
#include "constexpr_if.hpp"

//   The ternary operator (cond ? a : b) used in the get method only works for types which can be
//   casted into each other (e.g. double and int).
//
//   Modify my_tuple so that the following can work
//
// int main(){
//   my_tuple<double, std::string> t_(3.4, "hello");
//   std::cout<<get<1>(t_)<<"\n";
// }
//
// NOTE: make use of the provided constexpr_if.hpp header.

template<typename ... T> struct my_tuple;

template<typename First, typename ... T>
struct my_tuple<First, T...> : public my_tuple<T ...> {
    using super=my_tuple<T ...>;
    static constexpr int size = sizeof...(T)+1;

    constexpr my_tuple(First first_, T ... rest_) : super(rest_ ...), m_value(first_){}

    template<int Id>
    constexpr auto get(){return Id==size ? m_value : super::template get<Id>();}

    First m_value;
};

template<typename First>
struct my_tuple<First> {
    constexpr my_tuple(First first_) : m_value(first_){}
    static constexpr int size = 1;
    template<int Id> constexpr First get(){return m_value;}
    First m_value;
};

template<int Id, typename Tuple>
constexpr auto get(Tuple t_){ return t_.template get<Tuple::size-Id>();}

int main(){
    my_tuple<double, std::string> t_(3.4, "Hello");
    std::cout<<get<1>(t_)<<"\n";
}
