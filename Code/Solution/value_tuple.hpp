#pragma once
#include <iostream>
//solution to exercice 1
#include "static_if.hpp"

namespace detail_ {
    template <int Index, typename Type>
    struct position{
        static_assert((Index > 0), "Index should be > 0");
        using value_type = Type;

        constexpr position(Type val) : value{val}
        {}

        static const int index=Index;
        Type value;
    };

    template <int N, typename First>
    constexpr auto initialize( )
    {
        return First{};
    }

    template <int N, typename First, typename X>
    constexpr auto initialize( X x )
    {
        //note: the ? construct does not allow x.value and 0 to have
        //different types

        //This prevents us from defining a generic tuple. How would
        // you solve this problem?  return (X::index==N? x.value : 0);

        //solution exercice 1:
        return static_if<X::index==N>::apply(x.value, First{});

    }

    template <int N, typename First, typename X, typename ... Rest>
    constexpr auto initialize(X x, Rest ... rest )
    {
        //note: the ? construct does not allow x.value and
        //initialize<N>(rest...) to have different types This prevents
        //us from defining a generic tuple. How would you solve this
        //problem?  return X::index==N? x.value :
        //initialize<N>(rest...);

        //solution exercice 1:
        return static_if<X::index==N>::apply( x.value, initialize<N, First>(rest...));
    }

    template<int NDim, typename ... Types >
    struct sized_value_tuple;

    template<int NDim, typename First, typename ... Types >
    struct sized_value_tuple<NDim, First, Types ...>
        : public sized_value_tuple<NDim, Types ...>
    {
    private:
        static const int n_dim=NDim;

        typedef sized_value_tuple<NDim, Types ...> super;

        static const int s_index=NDim - sizeof...(Types);

        template <int Limit>
        static constexpr bool check_bounds() {
            return true;
        };

        template <int Limit, typename _First, typename ...Elems>
        static constexpr bool check_bounds() {
            return (_First::index <= Limit) && check_bounds<Limit, Elems...>();
        };

    public:
        template <int Idx, typename Type, typename... GenericElements>
        constexpr sized_value_tuple ( position<Idx, Type> const& t,
                                      GenericElements const& ... x):
            super( t, x... ),
            m_offset(initialize<s_index, First>(t, x...))
        {
            static_assert(check_bounds<n_dim,
                          position<Idx, Type>,
                          GenericElements...>(), "Out of bound");
        }


        constexpr sized_value_tuple ():
            super(),
            m_offset(initialize<s_index, First>())
        { }

        template<int Idx>
        constexpr auto get() const {
            return static_if<Idx==s_index>
                ::apply(m_offset, super::template get<Idx>());
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
        constexpr sized_value_tuple ( GenericElements... ) {}

        constexpr sized_value_tuple ( ) {}

        static const int s_index=NDim+1;

        //never called
        template<int Idx>
        constexpr int get() const {
            static_assert((Idx<=n_dim),
                          "sized_value_tuple out of bound access");
            return 0; }
    };
} //namespace detail_

    template<int Index, typename Type>
    auto constexpr pos(Type value){
        static_assert((Index > 0), "Index should be > 0");
        return detail_::position<Index, Type>(value);
    }

    template<typename ... T>
    using value_tuple=detail_::sized_value_tuple<sizeof...(T), T...>;
