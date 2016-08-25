#include <iostream>

struct F{
    static int m_f ;
};

struct D{
    static int m_d ;
};

struct S {
    static int c;
};

int F::m_f = 10 * D::m_d ;

int D::m_d = 10 * S::c;

int S::c = 5;

int main()
{
    std::cout << "F::m_f = " << F::m_f << '\n';
    std::cout << "D::m_d::value = " << D::m_d << '\n';
    std::cout << "S::c::value = " << S::c << '\n';
    //std::array<int, S::c> a1; // OK: S::c is a constant expression
//  std::array<int, d> a2;    // error: d is not a constant expression
}
