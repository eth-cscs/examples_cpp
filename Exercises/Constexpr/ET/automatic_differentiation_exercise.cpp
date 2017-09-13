#include <iostream>

/**@brief Expression summing two arguments*/
namespace expressions {
template <typename T1, typename T2> struct expr_plus {
  T1 arg1;
  T2 arg2;

  constexpr expr_plus(T1 arg1, T2 arg2) : arg1(arg1), arg2(arg2) {}

  std::string to_string() const {
    return std::string("(") + arg1.to_string() + " + " + arg2.to_string() +
           std::string(")");
  }

  template <typename T> constexpr auto operator()(T t_) const {
    return arg1(t_) + arg2(t_);
  }
};

/** sum expression*/
template <typename T1, typename T2>
constexpr expr_plus<T1, T2> operator+(T1 arg1, T2 arg2) {
  return expr_plus<T1, T2>(arg1, arg2);
}

template <typename T1, typename T2> struct expr_times {
  T1 arg1;
  T2 arg2;

  constexpr expr_times(T1 arg1, T2 arg2) : arg1(arg1), arg2(arg2) {}

  template <typename T> constexpr auto operator()(T t_) const {
    return arg1(t_) * arg2(t_);
  }

  std::string to_string() const {
    return std::string("(") + arg1.to_string() + " * " + arg2.to_string() +
           std::string(")");
  }
};

/** sum expression*/
template <typename T1, typename T2>
constexpr expr_times<T1, T2> operator*(T1 arg1, T2 arg2) {
  return expr_times<T1, T2>(arg1, arg2);
}

template <typename U> struct p {

  using value_type = U;

    p() {}

  template <typename T> constexpr T operator()(T t_) const { return t_; }
  std::string to_string() const { return std::string(" x "); }
};

constexpr auto x = p<int>();

    template <typename T> struct c {
  T value;

  constexpr c(T x) : value{x} {};

  operator T() const { return value; }

  template <typename U> constexpr T operator()(U) const { return value; }

  std::string to_string() const { return "{" + std::to_string(value) + "}"; }
};

template <typename T1> struct expand_derivative;

template <typename T1> constexpr auto D(T1 arg1) {
  return expand_derivative<T1>(arg1)();
}

template <typename T> struct expand_derivative<p<T>> {

  constexpr expand_derivative(p<T>) {}

  constexpr auto operator()() const { return c<T>{1}; }
};

template <typename U> struct expand_derivative<c<U>> {

  constexpr expand_derivative(c<U>) {}

  constexpr auto operator()() const { return c<U>{0}; }
};

template <typename T1, typename T2>
struct expand_derivative<expr_plus<T1, T2>> {

  expr_plus<T1, T2> arg1;

  constexpr expand_derivative(expr_plus<T1, T2> arg) : arg1(arg) {}

  constexpr auto operator()() { return D(arg1.arg1) + D(arg1.arg2); }
};

template <typename T1, typename T2>
struct expand_derivative<expr_times<T1, T2>> {

  expr_times<T1, T2> arg1;

  constexpr expand_derivative(expr_times<T1, T2> arg1) : arg1(arg1) {}

  constexpr auto operator()() const {
    return D(arg1.arg1) * arg1.arg2 + arg1.arg1 * D(arg1.arg2);
  }
};

} // namespace expressions

using namespace expressions;
int main() {
  constexpr auto expr = x * x + x * x * x * c<int>{3};
  std::cout << expr.to_string() << "\n";
  std::cout << "value of E in 4: " << expr(4) << "\n";

  std::cout << "derivative: " << D(expr).to_string() << "\n";
  std::cout << "value of D in 4: " << D(expr)(4) << "\n";

  std::cout << "derivative of derivative: " << D(D(expr)).to_string() << "\n";
  std::cout << "value of D in 4: " << D(D(expr))(4) << "\n";

  static_assert(expr(4) == 208, "error");
  static_assert(D(expr)(4) == 152, "error");
  static_assert(D(D(expr))(4) == 74, "error");

  // Can you make the following to work?
  // You can start with regular runtime calls, and then
  // make them constexpr (much easier than typical TMP
  // where the runtime and compile time branches are
  // completely different!

  //static_assert(expr.sum_ops() == 1, "error");
  //static_assert(expr).sum_mult() == 4, "error");
}
