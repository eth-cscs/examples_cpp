#include <iostream>
struct S {
    static constexpr int s_c = 5;
};
struct D{
    static constexpr int s_d = 10 * S::s_c ;
};
struct F{
    static constexpr int s_f = 10 * D::s_d ;
};
constexpr int F::s_f;
constexpr int D::s_d;
constexpr int S::s_c;
int main(){
    std::cout << "s_f = " << F::s_f << '\n'; // 500
    std::cout << "s_d = " << D::s_d << '\n'; // 50
    std::cout << "s_c = " << S::s_c << '\n';}// 5
