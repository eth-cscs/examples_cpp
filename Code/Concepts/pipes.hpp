#pragma once

#include <type_traits>
#include <utility>

namespace pipes {

template <class Arg, class F,
          std::enable_if_t<std::is_invocable_v<F, Arg>, int> = 0>
auto operator|(Arg &&arg, F f) {
  return f(std::forward<Arg>(arg));
};

template <class F, class G,
          std::enable_if_t<!std::is_invocable_v<G, F>, int> = 0>
auto operator|(F f, G g) {
  return [f = std::move(f), g = std::move(g)](auto &&... args) {
    return g(f(std::forward<decltype(args)>(args)...));
  };
}

} // namespace pipes
