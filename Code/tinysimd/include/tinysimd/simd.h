#pragma once

#include <type_traits>

#include <tinysimd/avx2.h>
#include <tinysimd/common.h>
#include <tinysimd/generic.h>

// Pick 'best' available match out of available ABIs.

namespace tinysimd {

template <typename...>
struct first_not_void_of { using type = void; };

template <typename... Rest>
struct first_not_void_of<void, Rest...> {
    using type = typename first_not_void_of<Rest...>::type;
};

template <typename T, typename... Rest>
struct first_not_void_of<T, Rest...> {
    using type = T;
};

namespace abi {

template <typename T, unsigned N> struct default_abi {
    using type = typename first_not_void_of<
        typename avx2<T, N>::type,
        typename generic<T, N>::type
    >::type;
};

} // namespace abi

template <typename I> struct simd_wrap;

template <typename I, typename T> struct indirect_expression {
    using index_type = typename simd_traits<I>::vector_type;
    T* p;
    index_type index;
    constraint c;

    indirect_expression(T* p, const index_type& index, constraint c = constraint::none):
        p(p), index(index), c(c) {}

    template <typename J> indirect_expression& operator=(const simd_wrap<J>& a) {
        a.copy_to(*this);
        return *this;
    }

    template <typename J> indirect_expression& operator+=(const simd_wrap<J>& a) {
        J::scatter_add(tag<I>{}, a.value_, p, index, c);
        return *this;
    }
};

template <typename I> struct simd_wrap {
private:
    static_assert(!std::is_void<I>::value, "unsupported SIMD ABI");

    using vector_type = typename simd_traits<I>::vector_type;
    vector_type value_;

    static simd_wrap wrap(const vector_type& v) {
        simd_wrap s;
        s.value_ = v;
        return s;
    }

public:
    using scalar_type = typename simd_traits<I>::scalar_type;
    static constexpr unsigned width = simd_traits<I>::width;

    simd_wrap() = default;
    simd_wrap(const simd_wrap& other) = default;

    simd_wrap(scalar_type x):
        value_(I::broadcast(x)) {}

    simd_wrap(const scalar_type (&a)[width]):
        value_(I::copy_from(a)) {}

    explicit simd_wrap(const scalar_type *p):
        value_(I::copy_from(p)) {}

    template <typename J>
    simd_wrap(indirect_expression<J, const scalar_type> pi):
        value_(I::gather(tag<J>{}, pi.p, pi.index, pi.c)) {}

    template <typename J>
    simd_wrap(indirect_expression<J, scalar_type> pi):
        value_(I::gather(tag<J>{}, pi.p, pi.index, pi.c)) {}

    simd_wrap& operator=(const simd_wrap& other) = default;
    simd_wrap& operator=(const scalar_type& x) {
        value_ = I::broadcast(x); return *this;
    }

    void copy_to(scalar_type* p) const {
        I::copy_to(value_, p);
    }

    template <typename J>
    void copy_to(indirect_expression<J, scalar_type> pi) const {
        I::scatter(tag<J>{}, value_, pi.p, pi.index, pi.c);
    }

    friend simd_wrap operator+(const simd_wrap& a, const simd_wrap& b) {
        return wrap(I::add(a.value_, b.value_));
    }

    friend simd_wrap operator*(const simd_wrap& a, const simd_wrap& b) {
        return wrap(I::mul(a.value_, b.value_));
    }

    friend simd_wrap fma(const simd_wrap& a, const simd_wrap& b, const simd_wrap& c) {
        return wrap(I::fma(a.value_, b.value_, c.value_));
    }

    friend scalar_type reduce(const simd_wrap& a) {
        return I::reduce_add(a.value_);
    }

    simd_wrap& operator+=(const simd_wrap& a) {
        value_ = I::add(value_, a.value_);
        return *this;
    }

    simd_wrap& operator*=(const simd_wrap& a) {
        value_ = I::mul(value_, a.value_);
        return *this;
    }

    struct element_proxy {
        vector_type* vptr;
        int i;

        element_proxy operator=(scalar_type x) {
            I::set_element(*vptr, i, x);
            return *this;
        }
        operator scalar_type() const { return I::element(*vptr, i); }
    };

    element_proxy operator[](int i) {
        return element_proxy{&value_, i};
    }

    scalar_type operator[](int i) const {
        return I::element(value_, i);
    }

    template <typename J>
    void compound_add_to(const indirect_expression<J,  scalar_type>& pi) {
        I::scatter_reduce_add(tag<J>{}, value_, pi.p, pi.index, pi.c);
    }

    template <typename Ptr, typename = std::enable_if_t<std::is_pointer<Ptr>::value>>
    friend auto indirect(Ptr p, const simd_wrap& index, constraint c = constraint::none) {
        using V = std::remove_reference_t<decltype(*p)>;
        return indirect_expression<I, V>(p, index.value_, c);
    }

    template <typename J, typename V>
    friend struct indirect_expression;
};

template <typename V, unsigned N, template <typename,unsigned> class abi = abi::default_abi>
using simd = simd_wrap<typename abi<V, N>::type>;


} // namespace tinysimd

