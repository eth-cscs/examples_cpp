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
    movable(movable&& other) {
        pv = other.pv;
        other.pv=nullptr;
        s=other.s;
        other.s=0;
        std::cout << "Move\n";
    }
    movable(movable const & other) {
        s=other.s;
        if (pv) {
            delete[] pv;
        }
        pv = new int[s];
        std::copy(other.pv, other.pv+other.s, pv);
        std::cout << "Copy\n";
    }

    ~movable() {
        if (pv) {
            delete [] pv;
        }
    }

    int size() const {return s;}
};

int main() {
    movable x(100);
    movable y(x); // copy constructor: x is lvalue

    movable z(movable(200)); // move constructor
    SHOW(z.size()); // prints 200
    movable u(std::move(z)); // move constructor
    SHOW(z.size()); // prints 0
    SHOW(u.size()); // prints 200
}
