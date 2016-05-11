#include "expressions.hpp"

using namespace expressions;
int main(){

    constexpr auto expr = p()+p()*p()*p();
    std::cout<<expr.to_string();
    std::cout<<" = ";
    std::cout<< expr(3)<<std::endl;
    std::cout<< "derivative: "<< D(expr)(3)<<std::endl;
    // static_assert(evaluation::value(expr)==11., "error");
}
