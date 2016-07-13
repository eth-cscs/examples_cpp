#include "../show.h"

#include <vector>
#include <array>

template <typename V>
auto generate() {
    return V{1,2,3,4,5};
}


template <typename SequenceType>
void test() {
    // Here generate calls initializer_list constructor of the vector
    auto x = generate<SequenceType>();

    for (auto i: x) {
        std::cout << i << ",";
    }
    std::cout << "\n";
}

int main() {
    test<std::vector<int>>(); // Initializes the vector calling the initializer_list constructor
    test<std::array<int,5>>(); // Initializes the array by aggregate initialization
}