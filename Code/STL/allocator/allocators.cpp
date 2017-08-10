#include<memory>
#include<vector>
#include<cstdlib>
#include<cassert>
#include<iostream>

#include "stack.hpp"
#include "heap.hpp"

void heap() {
    std::cout << " >> heap allocator <<\n";

    std::vector<int,  my_heap_allocator<int> > q_({0,1,2,3,4,5,6,7});
    assert(q_[2]==2);

    try {
        std::vector<int,  my_heap_allocator<int> > q_(101); //throws bad_alloc
    } catch (std::bad_alloc const&) {
        std::cout << "Only 100 elements are allowed\n";
    }
}

void stack() {
    std::cout << " >> stack allocator <<\n";

    std::vector<int,  my_stack_allocator<int> > q_({0,1,2,3,4,5,6,7});
    assert(q_[2]==2);

    try {
        std::vector<int,  my_stack_allocator<int> > q_(101); //throws bad_alloc
    } catch (std::bad_alloc const&) {
        std::cout << "Only 100 elements are allowed\n";
    }
}


int main() {

    std::cout << " > allocators <\n";

    heap();

    stack();
}
