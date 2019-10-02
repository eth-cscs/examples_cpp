#include <iostream>

struct A {
    int generation = 0;
    A() { std::cout << "D " << generation << "\n"; }
    //A(A const& a) : generation{a.generation+1} { std::cout << "C " << generation << "\n"; }
    A& operator=(A const& a) { generation = a.generation+1; std::cout << "A " << generation << "\n"; return *this; };
    ~A() { std::cout << "X " << generation << "\n"; };
};

int main() {
    A a;
    A b{a};
    A c = b;
    A d;
    d = c;
}
