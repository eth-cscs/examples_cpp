#include <iostream>
#include <vector>

template <typename T>
struct my_allocator {
    using value_type = T;
    T* allocate(std::size_t s) const {return new T[s];}
    void deallocate(T* p, std::size_t) const {delete [] p;}
};

template <typename T>
using my_vec = std::vector<T, my_allocator<T>>;

template <typename T>
std::size_t size_of(my_vec<T> const& v) {
    return v.size();
}

// The following code redefined the previous size_of. my_vec is not a new type!
// template <typename T>
// std::size_t size_of(std::vector<T, my_allocator<T>> const& v) {
//     return v.size();
// }

template <template <typename, typename> class V>
void do_nothing(V<int, my_allocator<int>> const&) {
    std::cout << "This is executed\n";
}

// If you comment the previous do_nothing,this one will not be picked
// up.  my_vec, as a type, is a template with 2 arguments!
template <template <typename> class V>
void do_nothing(V<int> const&) {
    std::cout << "this is never executed\n";
}

int main() {
    std::cout << size_of(my_vec<int>(10)) << "\n";

    do_nothing(my_vec<int>(23));
}
