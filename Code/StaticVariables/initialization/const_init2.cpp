#include <iostream>

class my_int{
    public:
    constexpr my_int(int val_) : value(val_){
    }
    int value;
};

struct D{
    static constexpr my_int m_d = my_int(10);
};

struct S {
    static constexpr my_int c =my_int(5 * (D::m_d.value));
};

static int const d = 10 * (D::m_d.value));

constexpr my_int D::m_d;

constexpr my_int S::c;

int main()
{
    std::cout << "d = " << d << '\n';
    std::cout << "D::m_d::value = " << D::m_d.value << '\n';
    std::cout << "S::c::value = " << S::c.value << '\n';
}
