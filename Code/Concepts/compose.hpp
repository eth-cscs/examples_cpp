#pragma once

#include <utility>

namespace composed_impl_ {
template <class... Fs> struct composed_f;

template <class F, class G> struct composed_f<F, G> {
  F f_;
  G g_;
  template <class... Args> decltype(auto) operator()(Args &&... args) const {
    return f_(g_(std::forward<Args>(args)...));
  }
};

template <class F, class... Fs>
struct composed_f<F, Fs...> : composed_f<F, composed_f<Fs...>> {
  composed_f(F f, Fs... fs)
      : composed_f<F, composed_f<Fs...>>{std::move(f), {std::move(fs)...}} {}
};

template <class... Fs> composed_f<Fs...> compose(Fs... fs) {
  return {std::move(fs)...};
}
} // namespace composed_impl_
using composed_impl_::compose;
