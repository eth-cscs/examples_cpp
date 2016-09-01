#include "../show.h"

struct A {

    int a;
    int *p;

    A(int _a) :a(_a), p(&a) {}

    void operator()() {
        DO((auto f = [=]() {int a=0; a++; std::cout << a << std::endl;}));
        DO((f()));
    }

    void alternate() { // !! WARNING: only this is copied by value
        DO((auto f = [=]() {a++; std::cout << a << std::endl;}));
        DO((f()));
    }

    void alternate2() { // This is the same as alternate
        DO((auto f = [=]() {this->a++; std::cout << this->a << std::endl;}));
        DO((f()));
    }

    void safe_version() {
        DO((int a = 5));
        DO((auto x = [=] () { std::cout << this->a << std::endl; std::cout << a << std::endl; }));
        DO((a = 3));
        DO((x()));
    }

    void out() const {
        std::cout << a << "\n";
    }
};


int main() {

    A a(10);

    DO((a()));

    DO((a.out()));

    DO((a.alternate()));
    DO((a.alternate2()));

    DO((a.out()));

    DO((a.safe_version()));
    DO((a.out()));
    return 0;
}
