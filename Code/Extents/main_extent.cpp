/**
Example for the computation of extents

current status:
computes the extents and puts them in a vector
TODO no make_independent is implemented yet
TODO no multiple stencils
TODO how does the fusion affect the computation?

*/

#include "functors.hpp"
#include "compute_extents.hpp"
#include "arg.hpp"
#include "make_stencil.hpp"

int main(){

    typedef argument<0> p1;
    typedef argument<1> p2;

    typedef functor1<> f;
    auto stencil = make_stencil(
        make_stage< f > (p1(),p2())
        ,make_stage< f > (p1(),p2())
        ,make_stage< f > (p1(),p2())
        );

    decltype(stencil)::extent_scan_t::fuck();
    decltype(stencil)::extent_map_t::fuck();
}
