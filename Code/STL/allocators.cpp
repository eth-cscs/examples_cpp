#include<vector>
#include<cstdlib>
#include<cassert>
#include<iostream>

template<typename T>
struct my_heap_allocator{
    using value_type=T;
    using propagate_on_container_move_assignment = std::true_type;
    using is_always_equal = std::true_type;

    T* allocate (int n, std::allocator<void>::const_pointer hint=0){
      if(n<100)  return static_cast<T*>(malloc(n*sizeof(T)));
      else throw(std::bad_alloc());
    }
    void deallocate (T* p, int n){free(p);}
};


template<typename T>
struct my_stack_allocator{
    T data[100];
    using value_type=T;
    using propagate_on_container_move_assignment = std::true_type;
    using is_always_equal = std::true_type;

    T* allocate (int n, std::allocator<void>::const_pointer hint=0){
      if(n<100)  return data;
      else throw(std::bad_alloc());
    }
    void deallocate (T* p, int n){/*RAII*/}
};

main(){
    std::vector<int,  my_stack_allocator<int> > q_({0,1,2,3,4,5,6,7});
    assert(q_[2]==2);
    std::cout<<q_.size()<<"\n";
    std::cout<<q_.capacity()<<"\n";
    q_.push_back(0);
    std::cout<<q_.size()<<"\n";
    std::cout<<q_.capacity()<<"\n";
    //std::vector<int,  my_allocator<int> > q_(101); //throws bad_alloc
}
