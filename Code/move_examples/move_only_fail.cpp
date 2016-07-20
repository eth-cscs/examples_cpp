#include <iostream>
#include <utility>
#include <vector>
#include "../show.h"

struct movable {
    std::vector<int> v;

    movable(int s) : v(s) {std::cout << "Default\n";}
    //movable(movable&& other) = delete; //: v(std::move(other.v)) {std::cout << "Move\n";}
    //movable(movable const & other) : v(other.v) {std::cout << "Copy\n";}
    //~movable() {}
};

int main() {
    movable z(movable(200));
    SHOW(z.v.size());
    movable u(std::move(z));
    SHOW(z.v.size());
    SHOW(u.v.size());
}
