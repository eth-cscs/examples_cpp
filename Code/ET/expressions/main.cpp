#include "expressions.hpp"

using namespace expressions;
int main(){
    constexpr auto expr = x+x*x*x;
    std::cout<<expr.to_string();
    std::cout<<" = ";
    std::cout<< expr(3)<<std::endl;
    std::cout<< "derivative: "<< D(expr)(3)<<std::endl;
    static_assert(expr(3)==30., "error");
    static_assert(D(expr)(3)==28., "error");
}
