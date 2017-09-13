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

    template <typename T> constexpr auto operator()(T t_) const -> decltype(arg1(t_) + arg2(t_))
    {
        return arg1(t_) + arg2(t_);
    }

  constexpr int sum_ops() const { return arg1.sum_ops() + arg2.sum_ops() + 1; }
  constexpr int mult_ops() const { return arg1.mult_ops() + arg2.mult_ops(); }
};

// This specialization is not useful for the functionality, but to
// reduce the length of the output expression
template <typename T> struct expr_plus<c<T>, c<T>> {
  c<T> value;

  constexpr expr_plus(c<T> arg1, c<T> arg2) : value{arg1.value + arg2.value} {}

  std::string to_string() const { return value.to_string(); }

  template <typename X> constexpr T operator()(X) const {
    return value.value;
  }

  constexpr int sum_ops() const { return 0; }
  constexpr int mult_ops() const { return 0; }
};

/** sum expression*/
template <typename T1, typename T2>
constexpr expr_plus<T1, T2> operator+(T1 arg1, T2 arg2) {
  return expr_plus<T1, T2>(arg1, arg2);
}

/** sum expression for c<T> */
template <typename T1>
constexpr expr_plus<c<T1>, c<T1>> operator+(c<T1> arg1, c<T1> arg2) {
  return c<T1>(arg1.value + arg2.value);
}

} // namespace expressions
