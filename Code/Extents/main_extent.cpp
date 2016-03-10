/**
Example for the computation of extents

current status:
computes the extents and puts them in a vector
TODO no multiple stencils
TODO how does the fusion affect the computation?

*/

#include "boost_includes.hpp"
#include "functors.hpp"
#include "compute_extents.hpp"
#include "arg.hpp"
#include "make_stencil.hpp"

int main(){

    typedef argument<0> p1;
    typedef argument<1> p2;

    typedef functor1<> f1;
    typedef functor2<> f2;
    typedef functor4<> f4;
    typedef functor3<> f3;
    auto stencil = make_stencil(
        make_stage<f1>(p1())
        ,make_stage<f2>(p2())
        ,make_stage<f4>(p2())
        ,make_stage<f3>(p1(),p2())
        );

    compute_extent<f1>::type::fuck();//prints the restriction on the domain of f1, <012012>
    compute_extent<f2>::type::fuck();//prints the restriction on the domain of f2, <300300>
    compute_extent<f3>::type::fuck();//prints the restriction on the domain of f3, <412412>
}
