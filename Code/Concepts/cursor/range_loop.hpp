#pragma once

#include "concept.hpp"

namespace range_loop_impl_ {
struct stop {};

template <class Cur> struct cur_iter {
  Cur cur_;

  decltype(auto) operator*() const { return cursor::concept ::get(cur_); }
  void operator++() { cursor::concept ::next(cur_); }
  bool operator!=(stop) const { return !cursor::concept ::done(cur_); }
};

template <class Cur> cur_iter<Cur> begin(Cur &&cur) {
  return {std::forward<Cur>(cur)};
}
template <class Cur> stop end(Cur &&) { return {}; }
} // namespace range_loop_impl_

using range_loop_impl_::begin;
using range_loop_impl_::end;
