/**
   Implementing lazy expression templates and automatic differentiation
   exercice: count the number of sums and multiplications at compile time
*/

#include "expressions.hpp"

using namespace expressions;
int main() {
  constexpr auto expr = x * x + x * x * x * c<int>{3};
  std::cout << expr.to_string() << "\n";
  std::cout << "sums of E: " << expr.sum_ops() << "\n";
  std::cout << "multiplications of E: " << expr.mult_ops() << "\n";
  std::cout << "value of E in 4: " << expr(4) << "\n";

  std::cout << "derivative: " << D(expr).to_string() << "\n";
  std::cout << "sums of D: " << D(expr).sum_ops() << "\n";
  std::cout << "multiplications of D: " << D(expr).mult_ops() << "\n";
  std::cout << "value of D in 4: " << D(expr)(4) << "\n";

  std::cout << "derivative of derivative: " << D(D(expr)).to_string() << "\n";
  std::cout << "sums of D: " << D(D(expr)).sum_ops() << "\n";
  std::cout << "multiplications of D: " << D(D(expr)).mult_ops() << "\n";
  std::cout << "value of D in 4: " << D(D(expr))(4) << "\n";

  static_assert(expr(4) == 208, "error");
  static_assert(D(expr)(4) == 152, "error");
  static_assert(D(D(expr))(4) == 74, "error");

  static_assert(expr.sum_ops() == 1, "error");
  static_assert(D(D(expr)).sum_ops() == 7, "error");
}
