#pragma once
#include <array>
#include <iostream>
//solution to exercice 1
#include "make_value_tuple.hpp"

namespace detail_{


    template <typename RunTimeTuple, typename  CompileTimeTuple, CompileTimeTuple& CTuple>
    struct value_tuple_mixed{

        typedef value_tuple_mixed<RunTimeTuple, CompileTimeTuple, CTuple> type;
        static const short n_dim = RunTimeTuple::n_dim+CompileTimeTuple::n_dim;
        static const short n_dim_constexpr = CompileTimeTuple::n_dim;
        static const short n_dim_runtime = RunTimeTuple::n_dim;
        using constexpr_tuple_t = CompileTimeTuple;

        //constexpr copy constructor
        static constexpr constexpr_tuple_t s_args_constexpr{CTuple};

        RunTimeTuple m_args_runtime; //oversizing

        template<typename ... ArgsRuntime>
        constexpr
        value_tuple_mixed( ArgsRuntime const& ... args ): m_args_runtime(args...) {
        }

        // template <short Id, short Idx>
        // static constexpr bool not_contained(){
        //     return static_if<coordinates[Id]==Idx> ::apply( (Id ? not_contained<(Id ? Id-1 : 0) , Idx>() : false), true );
        // }

        //compile-time lookup
        template<short Idx>
        constexpr
        auto get() const {
            return
                static_if<(s_args_constexpr.template is_present<Idx>())>::apply(
                    s_args_constexpr
                    , m_args_runtime
                    ).template get<Idx>() ;
        }
    };

    //annoying verbosity
    template <typename RunTimeTuple, typename CompileTimeTuple, CompileTimeTuple& CTuple >
    constexpr const typename value_tuple_mixed<RunTimeTuple, CompileTimeTuple, CTuple>::constexpr_tuple_t value_tuple_mixed<RunTimeTuple, CompileTimeTuple, CTuple>::s_args_constexpr;

}//namespace detail
