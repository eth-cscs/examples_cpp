template<typename T>
struct my_heap_allocator{
    using value_type=T;

    T* allocate (int n, std::allocator<void>::const_pointer hint=0){
      if(n<100)  return static_cast<T*>(malloc(n*sizeof(T)));
      else throw(std::bad_alloc());
    }
    void deallocate (T* p, int n){free(p);}
};
