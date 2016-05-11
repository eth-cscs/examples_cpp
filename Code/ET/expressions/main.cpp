#include "expressions.hpp"

using namespace expressions;
int main(){

    constexpr auto expr = arg(3.)+arg(4.)+arg(4);
    std::cout<<expr.to_string();
    std::cout<<" = ";
    std::cout<< evaluation::value(expr)<<std::endl;
    std::cout<< "derivative: "<< evaluation::value(D(expr))<<std::endl;
    static_assert(evaluation::value(expr)==11., "error");
}
