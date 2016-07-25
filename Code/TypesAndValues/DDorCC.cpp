
// rounD Definition/Declaratin
// vs.
// Curly Construction/Creation


#include <vector>
#include <algorithm>
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
};

struct C {
    using value_type = float;
    std::vector<value_type> v;

    C(int i) : v(i) {}
    C(int i, value_type j) : v(i,j) {}
    C(std::initializer_list<value_type> const& l)
            : v(l)
    {}
};

OUT(A) {
    return s << "struct A {\n    int " << a.a << ", " << a.b << ";\n    struct {\n      int " << a.f.x << ", " << a.f.y << "\n    } f;\n}\n\n";
}

OUT(B) {
    s << "struct B {\n    <";
    for (auto i: a.v) { s << i << " ";}
    s << ">;\n [" << "size: " << a.v.size() << "\n};\n\n";
    return s;
}

OUT(C) {
    s << "struct C {\n    <";
    for (auto i: a.v) { s << i << " ";}
    s << ">;\n [" << "size: " << a.v.size() << "\n};\n\n";
    return s;
}

void test() {
    // aggregate
    {
        A x{2, 3, {4, 5}};
        SHOW(x);
    }
    {
        A x;
        SHOW(x);
    }
    {
        A x{};
        SHOW(x);
    }
    {
        A x = A();
        SHOW(x);
    }

    B b0{10};
    SHOW_PREFIX("B b0{10};", b0);

    B b1(10);
    SHOW_PREFIX("B b1(10);", b1);

    B b2{10,4};
    SHOW_PREFIX("B b2{10,4};", b2);

    B b3(10,4);
    SHOW_PREFIX("B b3(10,4);", b3);

    C c0{10};
    SHOW_PREFIX("C c0{10};",c0);

    C c1(10);
    SHOW_PREFIX("C c1(10);",c1);

    C c2{10,4.7};
    SHOW_PREFIX("C c2{10,4.7};",c2);

    C c3(10,4.7);
    SHOW_PREFIX("C c3(10,4.7);",c3);
}

int main() {
    test();
}
