#pragma once

#include <iostream>
#include <utility>

#include "concept.hpp"

namespace cursor {
namespace algo {
namespace impl_ {

template <class In> struct take_cur {
  static_assert(concept ::is_cursor<In>());

  int count_;
  In in_;

  take_cur(int n, In in)
      : count_(concept ::done(in) ? 0 : n), in_(std::move(in)) {}

  bool done() const { return count_ == 0; }
  decltype(auto) get() const { return concept ::get(in_); }
  void next() {
    concept ::next(in_);
    if (concept ::done(in_))
      count_ = 0;
    else
      --count_;
  }
};

inline constexpr auto take(int n) {
  return [n](auto in) { return take_cur(n, std::move(in)); };
}

template <class Pred, class In> struct filter_cur {
  static_assert(concept ::is_cursor<In>());

  Pred pred_;
  In in_;

  decltype(auto) get() const { return concept ::get(in_); }

  filter_cur(Pred pred, In in) : pred_(std::move(pred)), in_(std::move(in)) {
    skip();
  }
  void next() {
    concept ::next(in_);
    skip();
  }

  bool done() const { return concept ::done(in_); }

  void skip() {
    for (; !concept ::done(in_) && !pred_(concept ::get(in_));
         concept ::next(in_)) {
    }
  }
};

template <class Pred> auto filter(Pred pred) {
  return [=](auto in) {
    return filter_cur<Pred, decltype(in)>{std::move(pred), std::move(in)};
  };
}

template <class F, class In> struct transform_cur {
  static_assert(concept ::is_cursor<In>());

  F f_;
  In in_;

  auto get() const { return f_(concept ::get(in_)); }
  void next() { concept ::next(in_); }
  bool done() const { return concept ::done(in_); }
};

template <class F> auto transform(F f) {
  return [=](auto in) {
    return transform_cur<F, decltype(in)>{f, std::move(in)};
  };
}

inline constexpr auto dump = [](auto in) {
  for (; !concept ::done(in); concept ::next(in))
    std::cout << concept ::get(in) << std::endl;
};

} // namespace impl_

using impl_::dump;
using impl_::filter;
using impl_::take;
} // namespace algo
} // namespace cursor
