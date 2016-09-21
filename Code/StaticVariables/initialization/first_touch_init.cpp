#include <iostream>
static int D();
static int F();
static int S();

static int F(){
    std::cout<<"init F"<<std::endl;
    static int m_f=10 * D() ;
    return m_f;
}

static int D(){
    std::cout<<"init D"<<std::endl;
    static int m_d = 10 * S() ;
    return m_d;
}

static int S() {
    std::cout<<"init S"<<std::endl;
    static int m_c=5;
    return m_c;
}

int main()
{
    std::cout << "m_f = " << F() << '\n';
    std::cout << "m_d = " << D() << '\n';
    std::cout << "m_c = " << S() << '\n';
}
