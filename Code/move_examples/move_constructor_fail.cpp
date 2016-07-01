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
    //movable(movable&& other) = delete;
    movable(movable const & other) {
        s=other.s;
        if (pv) {
            delete[] pv;
        }
        pv = new int[s];
        std::copy(other.pv, other.pv+other.s, pv);
        std::cout << "Copy\n";
    }

    int size() const {return s;}
};

int main() {
    movable z(200);
    SHOW(z.size()); // prints 200
    movable u(std::move(z)); // move constructor
    SHOW(z.size()); // prints 0
    SHOW(u.size()); // prints 200
}
