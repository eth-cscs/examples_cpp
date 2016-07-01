#include <iostream>
#include <utility>
#include <vector>
#include "../show.h"

struct movable {
    std::vector<int> v;

    movable(int s) : v(s) {std::cout << "Default\n";}
    movable(movable&& other) : v(std::move(other.v)) {std::cout << "Move\n";}
    movable(movable const & other) : v(other.v) {std::cout << "Copy\n";}
};

int main() {
    movable x(100);
    movable y(x); // copy constructor: x is lvalue

    movable z(movable(200)); // move constructor
    SHOW(z.v.size()); // prints 200
    movable u(std::move(z)); // move constructor
    SHOW(z.v.size()); // prints 0
    SHOW(u.v.size()); // prints 200
}
