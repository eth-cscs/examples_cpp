#pragma once
#include <boost/mpl/at.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/plus.hpp>
#include "scan.hpp"

template<typename T1, typename T2>
struct sum_extent_binary{
    typedef typename sum_extent<T1, T2>::type type;
};

template <typename Extent>
struct lambda{

    template<typename T1, typename T2>
    struct apply{
        typedef typename boost::mpl::push_back<T1, typename subtract_extent<Extent, T2>::type >::type type;
    };
};

template <typename ... Stages>
struct stencil{
    typedef typename sum_extent<typename Stages::extent_t ...>::type extent_t;
    typedef typename scan_extent<typename Stages::extent_t ...>::type extent_scan_t;

    typedef typename boost::mpl::fold<
        extent_scan_t
        , boost::mpl::vector0<>
        , lambda<extent_t>
        >::type extent_map_t;


// boost::mpl::map<typename boost::mpl::pair<Stages, typename subtract_extent<extent_t, typename Stages::extent_t>::type>::type ... >::type extent_map_t;
};
