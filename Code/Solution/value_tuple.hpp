#pragma once
#include <type_traits>
//solution to exercice 1
#include "static_if.hpp"

namespace detail_ {
template <int Index, typename Type>
struct position{
    static_assert((Index > 0), "Index should be > 0");

    constexpr position(Type const& val) : value{val}
    {}

    static const int index=Index;
    Type value;
};

template <int N, typename X>
constexpr auto initialize( X const& x )
{
    //note: the ? construct does not allow x.value and 0 to have different types
    //This prevents us from defining a generic tuple. How would you solve this problem?
    // return (X::index==N? x.value : 0);

    //solution exercice 1:
    return static_if<X::index==N>::apply(x.value, 0);

}

template <int N, typename X, typename ... Rest>
constexpr auto initialize(X const& x, Rest const& ... rest )
{
    //note: the ? construct does not allow x.value and initialize<N>(rest...) to have different types
    //This prevents us from defining a generic tuple. How would you solve this problem?
    //return X::index==N? x.value : initialize<N>(rest...);

    //solution exercice 1:
    return static_if<X::index==N>::apply( x.value, initialize<N>(rest...));
}

template<int NDim, typename ... Types >
struct sized_value_tuple;


template<typename T, int Idx>
struct access{
    using type = typename std::conditional<Idx==1, T, typename access<typename T::super, Idx-1>::type >::type;
};

template<typename T>
struct access<T, 1>{
    using type = T;
};


template<int NDim, typename First, typename ... Types >
struct sized_value_tuple<NDim, First, Types ...> : public sized_value_tuple<NDim, Types ...>
{
    static const int n_dim=NDim;

    typedef sized_value_tuple<NDim, Types ...> super;
    static const int n_args=sizeof...(Types)+1;

    template <int Idx, typename Type, typename... GenericElements>
    constexpr sized_value_tuple ( position<Idx, Type> const& t, GenericElements const& ... x):
        super( t, x... ), m_offset(initialize<n_dim-n_args+1>(t, x...)) {
    }

    template <int Idx, typename Type, typename... GenericElements>
    constexpr offset_tuple ( dimension<Idx, Type> & t, GenericElements & ... x):
        super( t, x... ), m_offset(initialize<n_dim-n_args+1>(t, x...)) {
    }

    template<int Idx>
    constexpr auto get() const {
        static_assert(Idx <= NDim, "error");
        return static_if<NDim-Idx==n_args-1>::apply( m_offset , super::template get<Idx>());
    }

    template<int Idx, typename T>
    void set(T const& arg_) {

        access<offset_tuple,Idx>::type::m_offset = arg_;
    }

    protected:
    First m_offset;
};

//recursion anchor
template< int NDim >
struct sized_value_tuple<NDim>
{
    static const int n_dim=NDim;

    template <typename... GenericElements>
    constexpr sized_value_tuple ( GenericElements... x) {}

    template <int Idx, typename Type, typename... GenericElements>
    constexpr offset_tuple ( dimension<Idx, Type> const& t, GenericElements const& ... x):
        m_offset(initialize<n_dim-n_args+1>(t, x...) ) {
    }

    template <int Idx, typename Type, typename... GenericElements>
    constexpr offset_tuple ( dimension<Idx, Type> & t, GenericElements & ... x):
        m_offset(initialize<n_dim-n_args+1>(t, x...) ) {
    }

    template<int Idx>
    constexpr int get() const { static_assert((Idx<=n_dim), "sized_value_tuple out of bound access"); return 0; }
};
} //namespace detail_

template<int Index, typename Type>
auto constexpr pos(Type const& value){
    static_assert((Index > 0), "Index should be > 0");
    return detail_::position<Index, Type>(value);
}

template<typename ... T>
using value_tuple=detail_::sized_value_tuple<sizeof...(T), T...>;
