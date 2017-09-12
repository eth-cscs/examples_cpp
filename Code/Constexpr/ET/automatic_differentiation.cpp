/**
   Implementing lazy expression templates and automatic differentiation
   exercice: count the number of sums and multiplications at compile time
*/

#include "expressions.hpp"

using namespace expressions;
int main(){
    constexpr auto expr = x*x+x*x*x*c<int>{3};
    std::cout<<expr.to_string() << "\n";
    std::cout<< "sums of E: "<< expr.sum_ops()<<std::endl;
    std::cout<< "multiplications of E: "<< expr.mult_ops()<<std::endl;
    std::cout << "value of E in 4: " << expr(4) << "\n";

    std::cout<< "derivative: "<< D(expr).to_string()<<std::endl;
    std::cout<< "sums of D: "<< D(expr).sum_ops()<<std::endl;
    std::cout<< "multiplications of D: "<< D(expr).mult_ops()<<std::endl;
    std::cout << "value of D in 4: " << D(expr)(4) << "\n";


    //std::cout<< "derivative of derivative: "<< D(D(x+x))(4)/*.to_string()*/<<std::endl;
    // std::cout<< "sums of D: "<< D(expr).sum_ops()<<std::endl;
    // std::cout<< "multiplications of D: "<< D(expr).mult_ops()<<std::endl;
    // std::cout << "value of D in 4: " << D(expr)(4) << "\n";

    //static_assert(expr(4)==72, "error");
    // static_assert(D(expr)(4)==50, "error");

}
