namespace expressions {

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

  constexpr int sum_ops() const { return arg1.sum_ops() + arg2.sum_ops(); }
  constexpr int mult_ops() const {
    return arg1.mult_ops() + arg2.mult_ops() + 1;
  }
};

// This specialization is not useful for the functionality, but to
// reduce the length of the output expression
template <typename T, typename X> struct expr_times<c<T>, c<X>> {
  c<T> value;

  constexpr expr_times(c<T> arg1, c<X> arg2) : value{arg1.value * arg2.value} {}

  template <typename U> constexpr auto operator()(U) const {
    return value.value;
    ;
  }

  std::string to_string() const { return value.to_string(); }

  constexpr int sum_ops() const { return 0; }
  constexpr int mult_ops() const { return 0; }
};

/** sum expression*/
template <typename T1, typename T2>
constexpr expr_times<T1, T2> operator*(T1 arg1, T2 arg2) {
  return expr_times<T1, T2>(arg1, arg2);
}
} // namespace expressions
