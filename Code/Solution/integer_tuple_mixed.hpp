#pragma once
#include <array>
#include <iostream>
//solution to exercice 1
#include "make_value_tuple.hpp"

namespace detail_{


    template <typename RunTimeTuple, typename ... Pair>
    struct integer_tuple_mixed{

        typedef integer_tuple_mixed<RunTimeTuple, Pair ...> type;
        static const short n_dim = RunTimeTuple::n_dim+sizeof...(Pair);
        static const short n_dim_constexpr = sizeof...(Pair);
        static const short n_dim_runtime = RunTimeTuple::n_dim;
        using constexpr_tuple_t = make_value_tuple<int, n_dim>;
        using array_t = std::array<short, n_dim_constexpr>;

        static constexpr constexpr_tuple_t s_args_constexpr{
            position<Pair::first, int>{Pair::second} ... };

        make_value_tuple<int, n_dim> m_args_runtime; //oversizing
        static constexpr array_t coordinates {Pair::first ... };

        template<typename ... ArgsRuntime>
        constexpr
        integer_tuple_mixed( ArgsRuntime const& ... args ): m_args_runtime(args...) {
        }

        template <short Id, short Idx>
        static constexpr bool not_contained(){
            return static_if<coordinates[Id]==Idx> ::apply( (Id ? not_contained<(Id ? Id-1 : 0) , Idx>() : false), true );
        }

        //compile-time lookup
        template<short Idx>
        constexpr
        auto get() const {
            return
                static_if<not_contained<n_dim_constexpr-1, Idx>()>::apply(
                    m_args_runtime
                    , s_args_constexpr
                    ).template get<Idx>() ;
        }
    };

    //annoying verbosity
    template <typename RunTimeTuple, typename ... Pair>
    constexpr const typename integer_tuple_mixed<RunTimeTuple, Pair ...>::constexpr_tuple_t integer_tuple_mixed<RunTimeTuple, Pair ...>::s_args_constexpr;

    template <typename RunTimeTuple, typename ... Pair>
    constexpr const typename integer_tuple_mixed<RunTimeTuple, Pair ...>::array_t integer_tuple_mixed<RunTimeTuple, Pair ...>::coordinates;


    template<short Idx, typename MixedTuple>
    static constexpr auto get(MixedTuple const& m_tuple) {
        return static_if<(MixedTuple::template not_contained<MixedTuple::n_dim_constexpr-1, Idx>())>::apply(
            m_tuple.m_args_runtime
            , m_tuple.s_args_constexpr
            ).template get<Idx>() ;
    }

}//namespace detail
