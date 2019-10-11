#include <iostream>
#include <tuple>
#include <string>

#include "../show.h"

template <class ...Ts>
std::tuple<Ts...> values(Ts&&... as) {
    return std::make_tuple(std::forward<Ts>(as)...);
}

int main() {

    int a[2] = { 3,4 };

    auto [x, y] = a;
    std::cout << x << ", " << y << "\n";

    auto [u, v, w] = values(3.4, std::string{"hello"}, 8);
    std::cout << u << ", "
              << v << ", "
              << w << "\n";
}
