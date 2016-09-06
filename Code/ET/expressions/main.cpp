/**
   Implementing lazy expression templates and automatic differentiation
   exercice: count the number of sums and multiplications at compile time
*/

#include "expressions.hpp"

using namespace expressions;
int main(){
    constexpr auto expr = D(D(x*x+x));
    std::cout<<expr.to_string();
    std::cout<<" = ";
    std::cout<< expr(3)<<std::endl;
    std::cout<< "derivative: "<< D(expr)(3)<<std::endl;
    std::cout<< "sums: "<< D(expr).sum_ops()<<std::endl;
    std::cout<< "multiplications: "<< D(expr).mult_ops()<<std::endl;
    // static_assert(expr(3)==30., "error");
    // static_assert(D(expr)(3)==28., "error");

}
