#pragma once

template <typename First, typename ... Extents>
struct subtract_extent{

    typedef typename subtract_extent<Extents ...>::type S;
    typedef extent<typename boost::mpl::minus<typename arg<0,First>::type, typename arg<0,S>::type >::type
                   , typename boost::mpl::minus<typename arg<1,First>::type, typename arg<1,S>::type >::type
                   , typename boost::mpl::minus<typename arg<2,First>::type, typename arg<2,S>::type >::type
                   , typename boost::mpl::minus<typename arg<3,First>::type, typename arg<3,S>::type >::type
                   , typename boost::mpl::minus<typename arg<4,First>::type, typename arg<4,S>::type >::type
                   , typename boost::mpl::minus<typename arg<5,First>::type, typename arg<5,S>::type >::type
                   > type;
};


template <typename First>
struct subtract_extent<First>{
    typedef First type;
};
