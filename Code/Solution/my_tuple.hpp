#pragma once

//solution to exercice 1
#include "static_if.hpp"

template <int Coordinate, typename Type>
struct dimension{
    static_assert((Coordinate > 0), "Index should be > 0");

    constexpr dimension(Type const& val) : value{val}
    {}

    static const int direction=Coordinate;
    Type value;
};

template<int Coordinate, typename Type>
auto constexpr arg(Type const& value){
    static_assert((Coordinate > 0), "Index should be > 0");
    return dimension<Coordinate, Type>(value);
}

template <int N, typename X>
constexpr decltype(auto) initialize( X const& x )
{
    //note: the ? construct does not allow x.value and 0 to have different types
    //This prevents us from defining a generic tuple. How would you solve this problem?
    // return (X::direction==N? x.value : 0);

    //solution exercice 1:
    return static_if<X::direction==N>::apply(x.value, 0);

}

template <int N, typename X, typename ... Rest>
constexpr decltype(auto) initialize(X const& x, Rest const& ... rest )
{
    //note: the ? construct does not allow x.value and initialize<N>(rest...) to have different types
    //This prevents us from defining a generic tuple. How would you solve this problem?
    //return X::direction==N? x.value : initialize<N>(rest...);

    //solution exercice 1:
    return static_if<X::direction==N>::apply( x.value, initialize<N>(rest...));
}

template<int NDim, typename ... Types >
struct offset_tuple;

template<int NDim, typename First, typename ... Types >
struct offset_tuple<NDim, First, Types ...> : public offset_tuple<NDim, Types ...>
{
    static const int n_dim=NDim;

    typedef offset_tuple<NDim, Types ...> super;
    static const int n_args=sizeof...(Types)+1;

    template <int Idx, typename Type, typename... GenericElements>
    constexpr offset_tuple ( dimension<Idx, Type> const& t, GenericElements const& ... x):
        super( t, x... ), m_offset(initialize<n_dim-n_args+1>(t, x...)) {
    }

    template<int Idx>
    constexpr decltype(auto) get() const {
        static_assert(Idx <= NDim, "error");
        return static_if<NDim-Idx==n_args-1>::apply( m_offset , super::template get<Idx>());
    }

    protected:
    First m_offset;
};

//recursion anchor
template< int NDim, typename First >
struct offset_tuple<NDim, First>
{
    static const int n_dim=NDim;

    static const int n_args=1;

    template <int Idx, typename Type, typename... GenericElements>
    constexpr offset_tuple ( dimension<Idx, Type> const& t, GenericElements const& ... x):
        m_offset(initialize<n_dim-n_args+1>(t, x...) ) {
    }

    template<int Idx>
    constexpr decltype(auto) get() const {
        return m_offset;
    }

protected:
    First m_offset;

};

template<typename ... T>
using my_tuple=offset_tuple<sizeof...(T), T...>;
