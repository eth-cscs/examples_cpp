
#include <vector>
#include <list>
#include <cstdlib>
#include "../show.h"

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

template <template <typename, typename> class Container,
          typename ValueType, template <typename> class Allocator = std::allocator >
struct my_container {
    using value_type = ValueType;
    using ContainerType = Container<ValueType, Allocator<ValueType>>;
    ContainerType C;

    my_container(std::size_t size, ValueType const& init) : C(size, init) {}
};


int main() {
    my_container<std::vector, float, my_heap_allocator> my_vec(42, 42);
    SHOW(my_vec.C.size());
    my_container<std::list, std::vector<int, my_stack_allocator<int>> > my_list(1, std::vector<int, my_stack_allocator<int>>{1,2,3});
    my_list.C.push_back(typename decltype(my_list)::value_type{4,5,6,7});
    SHOW(my_list.C.size());
}