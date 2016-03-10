#pragma once

template <typename First, typename ... Extents>
struct sum_extent{

    typedef typename sum_extent<Extents ...>::type S;
    typedef extent<typename boost::mpl::plus<typename arg<0,First>::type, typename arg<0,S>::type >::type
                   , typename boost::mpl::plus<typename arg<1,First>::type, typename arg<1,S>::type >::type
                   , typename boost::mpl::plus<typename arg<2,First>::type, typename arg<2,S>::type >::type
                   , typename boost::mpl::plus<typename arg<3,First>::type, typename arg<3,S>::type >::type
                   , typename boost::mpl::plus<typename arg<4,First>::type, typename arg<4,S>::type >::type
                   , typename boost::mpl::plus<typename arg<5,First>::type, typename arg<5,S>::type >::type
                   > type;
};

template <typename First>
struct sum_extent<First>{
    typedef First type;
};
