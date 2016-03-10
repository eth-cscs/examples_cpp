#pragma once
#include "extents.hpp"

/*It would be a "placeholder" in GridTools, has no dependencies,
  and consequently is defined on the whole iteration space.
  It has an extent though, saying that the functors depending on this
  placeholder will have restrictions on the domain*/
template<typename Extent>
struct p1{
    typedef boost::mpl::vector0<> arg_list;
};

/* same as before */
template<typename Extent>
struct p2{
    typedef boost::mpl::vector0<> arg_list;
};

/* functor depending on p1 */
template<typename Extent=extent<> >
struct functor1{
    typedef p1<extent< 0,1,2,0,1,2 > > p_1;
    typedef boost::mpl::vector1<p_1> arg_list;
};

/* functor depending on p2 */
template<typename Extent=extent<> >
struct functor2{
    typedef p2<extent< 3,0,0,3,0,0 > > p_2;
    typedef boost::mpl::vector1<p_2> arg_list;
};

/* other functor depending on p2 */
template<typename Extent=extent<> >
struct functor4{
    typedef p2<extent< 4,0,0,4,0,0 > > p_2;
    typedef boost::mpl::vector1<p_2> arg_list;
};

/* functor depending on both functor1 and functor4 */
template<typename Extent=extent<> >
struct functor3{
    typedef functor1<extent<> > p_1;//these dependencies can be deduced by the make_stencil
    typedef functor4<extent<> > p_2;
    typedef boost::mpl::vector2<p_1,p_2> arg_list;
};
