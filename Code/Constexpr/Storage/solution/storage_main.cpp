#include "storage_info.hpp"

//solution to exercice
#include "storage_info_sol.hpp"

#include "storage.hpp"
#include <iostream>

int main(){

    //run-time instance
    storage_info<3> meta_(5,4,3);
    std::cout<<"meta_.index(1,0,0): "<<meta_.index(1,0,0)<<std::endl;
    std::cout<<"meta_.index(0,1,0): "<<meta_.index(0,1,0)<<std::endl;
    std::cout<<"meta_.index(0,0,1): "<<meta_.index(0,0,1)<<std::endl;

    //compile-time instance
    constexpr storage_info<5> c_meta_{2,3,4,5,6};
    static_assert(c_meta_.template dim<0>()==2, "error");
    static_assert(c_meta_.template dim<1>()==3, "error");
    static_assert(c_meta_.template dim<2>()==4, "error");
    static_assert(c_meta_.template dim<3>()==5, "error");
    static_assert(c_meta_.template dim<4>()==6, "error");
    static_assert(c_meta_.index(1,0,0,0,0)==1, "error");
    static_assert(c_meta_.index(0,1,0,0,0)==2, "error");
    static_assert(c_meta_.index(0,0,1,0,0)==3*2, "error");
    static_assert(c_meta_.index(0,0,0,1,0)==4*3*2, "error");
    static_assert(c_meta_.index(0,0,0,0,1)==5*4*3*2, "error");

    //exercice: add a storage layout template parameter, e.g.
    //storage_info<layout<0,1,2> > => increasing strides
    //storage_info<layout<2,1,0> > => decreasing strides
    //solution:
    constexpr storage_info_sol<layout_map<4,3,2,1,0> > c_meta_sol_{2,3,4,5,6};

    static_assert(c_meta_sol_.index(1,0,0,0,0)==6*5*4*3, "error");
    static_assert(c_meta_sol_.index(0,1,0,0,0)==6*5*4, "error");
    static_assert(c_meta_sol_.index(0,0,1,0,0)==6*5, "error");
    static_assert(c_meta_sol_.index(0,0,0,1,0)==6, "error");
    static_assert(c_meta_sol_.index(0,0,0,0,1)==1, "error");

}
