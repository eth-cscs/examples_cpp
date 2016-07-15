
// rounD Definition/Declaratin
// vs.
// Curly Construction/Creation


#include <vector>
#include "../show.h"

struct A {
        int a, b;
        struct {
            int x,y;
        } f;
};

struct B {
    std::vector<int> v;

    B(int i) : v(i) {}
    B(int i, int j) : v(i,j) {}

    void out() const {
        std::for_each(v.begin(), v.end(), [](const int i) { std::cout << i << ",";});
        std::cout << "\n";
    }
};

struct C {
    using value_type = float;
    std::vector<value_type> v;

    C(int i) : v(i) {}
    C(int i, value_type j) : v(i,j) {}
    C(std::initializer_list<value_type> const& l)
            : v(l)
    {}

    void out() const {
        std::for_each(v.begin(), v.end(), [](const value_type i) { std::cout << i << ",";});
        std::cout << "\n";
    }
};


template <typename T>
void foo(T const&) {
    using U = typename T::type;

}


int main() {
    // aggregate
    A x{2,3,{4,5}};
    SHOW(x.f.y);

    foo(x.f);
    B b0{10};
    SHOW(b0.v.size());
    b0.out();

    B b1(10);
    SHOW(b1.v.size());
    b1.out();

    B b2{10,4};
    SHOW(b2.v.size());
    b2.out();

    B b3(10,4);
    SHOW(b3.v.size());
    b3.out();

    C c0{10};
    SHOW(c0.v.size());
    c0.out();

    C c1(10);
    SHOW(c1.v.size());
    c1.out();

    C c2{10,4.7};
    SHOW(c2.v.size());
    c2.out();

    C c3(10,4.7);
    SHOW(c3.v.size());
    c3.out();
}