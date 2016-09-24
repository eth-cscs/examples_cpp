#include<iostream>
struct S {
    static int s_c;
};
struct D{
    static int s_d ;
};
struct F{
    static int s_f ;
};
int F::s_f = 10 * D::s_d;
int D::s_d = 10 * S::s_c;
int S::s_c = 5;
int main(){
    std::cout << "s_f = " << F::s_f << '\n'; // 0
    std::cout << "s_d = " << D::s_d << '\n'; // 50
    std::cout << "s_c = " << S::s_c << '\n';}// 5
