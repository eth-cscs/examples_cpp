#pragma once

template <typename First, typename ... Extents>
struct scan_extent{
typedef typename boost::mpl::push_back<typename scan_extent<Extents ...>::type, typename sum_extent<First, Extents ...>::type >::type type;
};

template <typename First>
struct scan_extent<First>{
typedef typename boost::mpl::vector1<First>::type type;
};
