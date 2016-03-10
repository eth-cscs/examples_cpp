#pragma once
#include<boost/mpl/fold.hpp>
#include<boost/mpl/push_back.hpp>
#include "enclosing_extent.hpp"
#include "sum_extent.hpp"
#include "subtract_extent.hpp"
#include "scan_extent.hpp"

struct sum_extent_lambda;
struct subtract_extent_lambda;
struct enclosing_extent_lambda;

template <typename Arg>
struct compute_extent;

template <template < typename E> class Arg, typename Extent>
struct compute_extent< Arg<Extent> >{

    typedef typename boost::mpl::fold<
        typename Arg<Extent>::arg_list
        , extent<>
        , enclosing_extent_lambda >::type extent_arguments_t;

    typedef typename enclosing_extent<Extent, extent_arguments_t>::type type;
};

struct sum_extent_lambda{

    template<typename T1, typename T2>
    struct apply{
        typedef typename sum_extent<T1, typename compute_extent<T2>::type >::type type;
    };
};

struct subtract_extent_lambda{

    template<typename T1, typename T2>
    struct apply{
        typedef typename subtract_extent<T1, typename compute_extent<T2>::type >::type type;
    };
};

struct enclosing_extent_lambda{

    template<typename T1, typename T2>
    struct apply{
        typedef typename enclosing_extent<T1, typename compute_extent<T2>::type >::type type;
    };
};
