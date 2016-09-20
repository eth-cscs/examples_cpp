#include<memory>
#include<vector>
#include<cstdlib>
#include<cassert>
#include<iostream>

//#include "stack.cpp"
#include "heap.cpp"

main(){
    std::vector<int,  my_heap_allocator<int> > q_({0,1,2,3,4,5,6,7});
    assert(q_[2]==2);
    //std::vector<int,  my_heap_allocator<int> > q_(101); //throws bad_alloc
}
