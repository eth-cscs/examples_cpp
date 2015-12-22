#pragma once
#include <iostream>
//solution to exercice 1
#include "static_if.hpp"

namespace detail_ {
    template <int Index, typename Type>
    struct position{
        static_assert((Index > 0), "Index should be > 0");
        using value_type = Type;

        constexpr position(Type const& val) : value{val}
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
    constexpr auto initialize( X const& x )
    {
        //note: the ? construct does not allow x.value and 0 to have
        //different types

        //This prevents us from defining a generic tuple. How would
        // you solve this problem?  return (X::index==N? x.value : 0);

        //solution exercice 1:
        return static_if<X::index==N>::apply(x.value, First{});

    }

    template <int N, typename First, typename X, typename ... Rest>
    constexpr auto initialize(X const& x, Rest const& ... rest )
    {
        //note: the ? construct does not allow x.value and
        //initialize<N>(rest...) to have different types This prevents
        //us from defining a generic tuple. How would you solve this
        //problem?  return X::index==N? x.value :
        //initialize<N>(rest...);

        //solution exercice 1:
        return static_if<X::index==N>::apply( x.value, initialize<N, First>(rest...));
    }


    template<typename T, int Idx>
    struct access{
        using type = typename std::conditional<Idx==1, T, typename access<typename T::super, Idx-1>::type >::type;
    };

    template<typename T>
    struct access<T, 1>{
        using type = T;
    };


    template<int NDim, typename ... Types >
    struct sized_value_tuple;

    template<int NDim, typename First, typename ... Types >
    struct sized_value_tuple<NDim, First, Types ...>
        : public sized_value_tuple<NDim, Types ...>
    {
    public:
        static const int n_dim=NDim;

        typedef sized_value_tuple<NDim, Types ...> super;

    private:

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
        constexpr sized_value_tuple ( position<Idx, Type> & t,
                                      GenericElements & ... x):
            super( t, x... ),
            m_offset(initialize<s_index, First>(t, x...))
        {
            static_assert(check_bounds<n_dim,
                          position<Idx, Type>,
                          GenericElements...>(), "Out of bound");
        }

        template <int Idx, typename Type, typename... GenericElements>
        constexpr sized_value_tuple ( position<Idx, Type> && t,
                                      GenericElements && ... x):
            sized_value_tuple(t, x...)
        {
        }

        constexpr sized_value_tuple ():
            super(),
            m_offset(initialize<s_index, First>())
        { }

        template<int Idx>
        constexpr auto get() const {
            static_assert(Idx <= NDim, "error");
            return static_if<Idx==s_index>
                ::apply(m_offset, super::template get<Idx>());
        }

        template<int Idx, typename T>
        void set(T const& arg_) {

            access<sized_value_tuple,Idx>::type::m_offset = arg_;
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
        constexpr sized_value_tuple ( GenericElements const& ... ) {}

        constexpr sized_value_tuple ( ) {}

        static const int s_index=NDim+1;

        //never called
        template<int Idx>
        constexpr int get() const {
            static_assert((Idx<=n_dim),
                          "sized_value_tuple out of bound access");
            return 0; }

        template<int Idx, typename T>
        void set(T const& arg_) {
        }

    };
} //namespace detail_

    template<int Index, typename Type>
    auto constexpr pos(Type value){
        static_assert((Index > 0), "Index should be > 0");
        return detail_::position<Index, Type>(value);
    }

    template<typename ... T>
    using value_tuple=detail_::sized_value_tuple<sizeof...(T), T...>;
