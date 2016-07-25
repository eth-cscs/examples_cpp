#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include "../show.h"

struct movable {
    int * pv = nullptr;
    int s = 0;

    movable() {}

    movable(int s) : pv{new int[s]}, s{s} {std::cout << "Default\n";}


    // The exixtence of a copy constructor prevent the automatic generation of the move constructor. Even if it's deleted.
    //   movable(movable const & other) = delete;

    int size() const {return s;}
};

int main() {
    movable z(200);
    SHOW(z.size()); // prints 200
    movable u(std::move(z)); // move constructor
    SHOW(z.size()); // prints 0
    SHOW(u.size()); // prints 200
}
