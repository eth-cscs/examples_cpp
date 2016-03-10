#pragma once
#include "extents.hpp"
#include <boost/mpl/vector.hpp>

template<typename Extent>
struct p1{
    typedef boost::mpl::vector0<> arg_list;
};

template<typename Extent>
struct p2{
    typedef boost::mpl::vector0<> arg_list;
};

template<typename Extent=extent<> >
struct functor1{
    typedef p1<extent< 0,1,2,0,1,2 > > p_1;
    typedef p2<extent< 0,1,2 > > p_2;
    typedef boost::mpl::vector2<p_1,p_2> arg_list;
};
