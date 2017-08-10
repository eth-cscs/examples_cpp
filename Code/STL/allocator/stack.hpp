template<typename T>
struct my_stack_allocator{
    T data[100];
    using value_type=T;

    T* allocate (int n, std::allocator<void>::const_pointer hint=0){
      if(n<100)  return data;
      else throw(std::bad_alloc());
    }
    void deallocate (T* p, int n){/*RAII*/}
};
