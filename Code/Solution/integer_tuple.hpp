#pragma once

//solution to exercice 1
#include "static_if.hpp"

namespace detail_ {
    template <int Index>
    struct position{
        static_assert((Index > 0), "Index should be > 0");

        constexpr position(int val) : value{val}
        {}

        static const int index=Index;
        int value;
    };

    template <std::size_t N>
    constexpr int initialize( )
    {
        return 0;
    }

    template <std::size_t N, typename X>
    constexpr int initialize( X x )
    {
        return X::index==N?x.value:initialize<N>();
    }

    template <std::size_t N, typename X, typename ... Rest>
    constexpr int initialize(X x, Rest ... rest )
    {
        return X::index==N?x.value:initialize<N>(rest...);
    }

    template<std::size_t NDim, std::size_t Index >
    struct sized_integer_tuple
        : public sized_integer_tuple<NDim, Index-1>
    {
    private:
        static const std::size_t n_dim=NDim;

        typedef sized_integer_tuple<NDim, Index-1> super;
        static const std::size_t n_args=Index;

        template <std::size_t Limit>
            static constexpr bool check_bounds() {
            return true;
        };

        template <std::size_t Limit, typename _First, typename ...Elems>
            static constexpr bool check_bounds() {
            return (_First::index <= Limit) && check_bounds<Limit, Elems...>();
        };

    public:
        template <int Idx, typename... GenericElements>
            constexpr sized_integer_tuple ( position<Idx> const& t,
                                            GenericElements const& ... x):
            super( t, x... ),
            m_offset(initialize<n_dim-n_args+1>(t, x...)) {
            static_assert(check_bounds<n_dim,
                          position<Idx>,
                          GenericElements...>(), "Out of bound");
        }


        constexpr sized_integer_tuple ():
            super(),
            m_offset(initialize<n_dim-n_args+1>())
                { }

        template<int Idx>
            constexpr int get() const {
            return static_if<NDim-Idx==n_args-1>
                ::apply(m_offset, super::template get<Idx>());
        }

    protected:
        int m_offset;
    };

    //recursion anchor
    template< std::size_t NDim >
    struct sized_integer_tuple<NDim, 0>
    {
        static const std::size_t n_dim=NDim;

        template <typename... GenericElements>
        constexpr sized_integer_tuple ( GenericElements... ) {}

        constexpr sized_integer_tuple ( ) {}

        static const std::size_t n_args=0;

        //never called
        template<int Idx>
        constexpr int get() const {
            static_assert((Idx<=n_dim),
                          "sized_integer_tuple out of bound access in get<>");
            return 0;
        }
    };
} //namespace detail_

template<int Index, typename Type>
auto constexpr pos(Type value){
    static_assert((Index > 0), "Index should be > 0");
    return detail_::position<Index>(value);
}

template<std::size_t Length>
using integer_tuple=detail_::sized_integer_tuple<Length, Length>;
