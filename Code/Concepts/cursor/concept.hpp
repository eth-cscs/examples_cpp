#pragma once

#include <type_traits>

namespace cursor {
namespace concept {
  namespace impl_ {

  template <int I> struct rank : rank<I - 1> {};

  template <> struct rank<0> {};

  template <class Ptr>
  auto dispatch_get(Ptr const &ptr, rank<2>) -> decltype(cursor_get(*ptr)) {
    return cursor_get(*ptr);
  }
  template <class Ptr>
  auto dispatch_get(Ptr const &ptr, rank<1>) -> decltype((*ptr).get()) {
    return (*ptr).get();
  }
  template <class Cur>
  auto dispatch_get(Cur const &cur, rank<0>) -> decltype(cur.get()) {
    return cur.get();
  }

  template <class Cur>
  auto cursor_get(Cur const &cur) -> decltype(dispatch_get(cur, rank<2>())) {
    return dispatch_get(cur, rank<2>());
  }

  template <class Cur> void cursor_next(Cur &cur);

  template <class Ptr>
  auto dispatch_next(Ptr &ptr, rank<2>) -> decltype(cursor_next(*ptr)) {
    return cursor_next(*ptr);
  }
  template <class Cur>
  auto dispatch_next(Cur &cur, rank<1>) -> decltype(cur.next()) {
    return cur.next();
  }
  template <class Cur> void dispatch_next(Cur &&, rank<0>) {}

  template <class Cur> void cursor_next(Cur &cur) {
    dispatch_next(cur, rank<2>());
  }

  template <class Cur> bool cursor_done(Cur const &);

  template <class Ptr>
  auto dispatch_done(Ptr const &ptr, rank<2>) -> decltype(cursor_done(*ptr)) {
    return cursor_done(*ptr);
  }
  template <class Cur>
  auto dispatch_done(Cur const &cur, rank<1>) -> decltype(cur.done()) {
    return cur.done();
  }
  template <class Cur> bool dispatch_done(Cur &&, rank<0>) { return false; }

  template <class Cur> bool cursor_done(Cur const &cur) {
    return dispatch_done(cur, rank<2>());
  }

  template <class Cur> auto cursor_consume(Cur &cur) {}

  inline constexpr auto done = [](auto const &cur) { return cursor_done(cur); };
  inline constexpr auto next = [](auto &cur) { cursor_next(cur); };
  inline constexpr auto get = [](auto const &cur) -> decltype(auto) {
    return cursor_get(cur);
  };
  inline constexpr auto consume = [](auto &cur) { return cursor_consume(cur); };

  template <class Cur>
  using value_type =
      std::decay_t<decltype(cursor_get(std::declval<Cur const &>()))>;

  template <class, class = void> struct is_cursor : std::false_type {};
  template <class Cur>
  struct is_cursor<
      Cur, std::enable_if_t<
               std::is_move_constructible_v<Cur> &&
               std::is_void_v<
                   std::void_t<decltype(cursor_next(std::declval<Cur &>()))>> &&
               std::is_lvalue_reference_v<decltype(
                   cursor_get(std::declval<Cur const &>()))> &&
               std::is_convertible_v<
                   decltype(cursor_done(std::declval<Cur const &>())), bool>>>
      : std::true_type {};

  } // namespace impl_

  using impl_::done;
  using impl_::get;
  using impl_::is_cursor;
  using impl_::next;
  using impl_::value_type;
} // namespace concept
} // namespace cursor
