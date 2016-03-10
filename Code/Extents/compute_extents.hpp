#pragma once
#include "enclosing_extent.hpp"
#include "sum_extent.hpp"

struct sum_extent_lambda;
struct subtract_extent_lambda;
struct enclosing_extent_lambda;

//algorithm:
// loop to compute the enclosing extent for each functor in the arg_list
// * given the first functor:
//   - compute the enclosing extent of its arg_list (recursively calling this metafunction)
//   - sum this extent to the first functor extent
// * pass to the next functor in the arg_list and reiterate

template <typename Functor, class Lambda=enclosing_extent_lambda>
struct compute_extent;

template <template < typename E> class Arg, typename Extent, class Lambda>
struct compute_extent< Arg<Extent>, Lambda >{

    typedef typename boost::mpl::fold<
        typename Arg<Extent>::arg_list
        , extent<>
        , Lambda >::type extent_arguments_t;//first step

    typedef typename enclosing_extent<Extent, extent_arguments_t>::type type;
};

struct enclosing_extent_lambda{

    template<typename T1, typename T2>
    struct apply{
        typedef typename enclosing_extent<T1, typename compute_extent<T2, sum_extent_lambda>::type >::type type;//second step
    };
};

struct sum_extent_lambda{

    template<typename T1, typename T2>
    struct apply{
        typedef typename sum_extent<T1, typename compute_extent<T2, enclosing_extent_lambda>::type >::type type;//fourth step: here eventually the recursion
    };
};
