#include <iostream>
static int D();
static int F();
static int S();

static int F(){
    static int m_f=10 * D() ;
    return m_f;
}

static int D(){
    static int m_d = 10 * S() ;
    return m_d;
}

static int S() {
    static int m_c=5;
    return m_c;
}

int main()
{
    std::cout << "F::m_f = " << F() << '\n';
    std::cout << "D::m_d::value = " << D() << '\n';
    std::cout << "S::c::value = " << S() << '\n';
}
