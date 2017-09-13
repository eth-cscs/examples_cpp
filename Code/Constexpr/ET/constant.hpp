#pragma once

template <typename T> struct c {
  T value;

  constexpr c(T x) : value{x} {};

  constexpr operator T() const { return value; }

  template <typename U> constexpr T operator()(U) const { return value; }

  std::string to_string() const { return "{" + std::to_string(value) + "}"; }

  constexpr int sum_ops() const { return 0; }

  constexpr int mult_ops() const { return 0; }
};
