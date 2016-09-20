//Exercice:
//transform the heap allocator  to a stack allocator

#include<vector>
#include<cstdlib>
#include<cassert>

template<typename T>
struct my_heap_allocator{
    using value_type=T;

    T* allocate (int n, std::allocator<void>::const_pointer hint=0){
      if(n<100)  return static_cast<T*>(malloc(n*sizeof(T)));
      else throw(std::bad_alloc());
    }
    void deallocate (T* p, int n){free(p);}
};

main(){
    std::vector<int,  my_heap_allocator<int> > q_({0,1,2,3,4,5,6,7});
    assert(q_[2]==2);
    //std::vector<int,  my_heap_allocator<int> > q_(101); //throws bad_alloc
}
