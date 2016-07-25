
#include <vector>
#include <list>

template <template <typename, typename> class Container,
          typename ValueType, typename Allocator = std::allocator<ValueType> >
struct my_container {
    using ContainerType = Container<ValueType, Allocator>;
    ContainerType C;

    template <typename ...Args>
    my_container(Args... args) : C(args...) {}
};


int main() {
    my_container<std::vector, float> my_vec(10,20);
    my_container<std::list, my_container<std::vector, int> > my_list;
    my_list.C.push_back(std::vector<int>{4,5,6,7});
}