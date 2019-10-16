#pragma once

#include <utility>

#include "concept.hpp"

namespace cursor {
template <class T> class any_cursor {
  struct iface {
    virtual ~iface() {}
    virtual T const &get() const = 0;
    virtual void next() = 0;
    virtual bool done() const = 0;
  };
  template <class Cur> struct impl : iface {
    Cur cur_;
    impl(Cur cur) : cur_(std::move(cur)) {}
    T const &get() const override { return concept ::get(cur_); }
    void next() override { concept ::next(cur_); }
    bool done() const override { return concept ::done(cur_); }
  };
  std::unique_ptr<iface> impl_;

public:
  template <class Cur>
  any_cursor(Cur cur) : impl_(new impl<Cur>{std::move(cur)}) {}

  T const &get() const { return impl_->get(); }
  void next() { impl_->next(); }
  bool done() const { return impl_->done(); }
};
} // namespace cursor
