#include <vector>


namespace step1 {
    struct my_container {
        using value_t = int;
        using container_t = std::vector<value_t>;
        container_t data;

        my_container(std::size_t s) : data(s) {}
    };

    int test() {
        my_container my_vec(42);
    }
} // namespace step1


namespace step2 {
    template <typename VT >
    struct my_container {
        using value_t = VT;
        using container_t = std::vector<value_t>;
        container_t data;

        my_container(std::size_t s) : data(s) {}
    };

    int test() {
        my_container<int> my_vec(42);
    }
} // namespace step2

namespace step3 {
    template <typename VT, typename Allocator = std::allocator<VT> >
    struct my_container {
        using value_t = VT;
        using container_t = std::vector<value_t, Allocator>;
        container_t data;

        my_container(std::size_t s) : data(s) {}
    };

    int test() {
        my_container<int> my_c1(42);
        my_container<int, std::allocator<int>> my_c2(42);
        // my_container<int, std::allocator<double>> my_c2(42);
    }
} // namespace step3

namespace step4 {
    template <typename VT,
              template <typename> class Allocator = std::allocator >
    struct my_container {
        using value_t = VT;
        using container_t = std::vector<value_t, Allocator<value_t>>;
        container_t data;

        my_container(std::size_t s) : data(s) {}
    };

    int test() {
        my_container<int> my_c1(42);
        my_container<int, std::allocator> my_c2(42);
    }
} // namespace step4

namespace step5 {
    template <typename CT>
    struct my_container {
        using value_t = typename CT::value_type;
        using container_t = CT;
        container_t data;

        my_container(std::size_t s) : data(s) {}
    };

    int test() {
        my_container<std::vector<int>> my_c1(42);
        my_container<std::vector<int, std::allocator<int>>> my_c2(42);
    }
} // namespace step5

namespace step6 {
    template <typename VT,
              template <typename,typename> class Container = std::vector,
              template <typename> class Allocator = std::allocator >
    struct my_container {
        using value_t = VT;
        using container_t = Container<value_t, Allocator<value_t>>;
        container_t data;

        my_container(std::size_t s) : data(s) {}
    };

    int test() {
        my_container<int> my_c1(42);
        my_container<int, std::vector> my_c2(42);
        my_container<int, std::vector, std::allocator> my_c3(42);
    }
} // namespace step6

int main() {
    step1::test();
    step2::test();
    step3::test();
    step4::test();
    step5::test();
    step6::test();
}
