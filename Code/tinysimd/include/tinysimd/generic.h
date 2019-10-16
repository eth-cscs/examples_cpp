#pragma once

#include <algorithm>
#include <array>
#include <iterator>
#include <tinysimd/common.h>

namespace tinysimd {

template <typename T, unsigned N>
struct generic;

namespace abi {

template <typename T, unsigned N>
struct generic { using type = ::tinysimd::generic<T, N>; };

} // namespace abi

template <typename T, unsigned N>
struct simd_traits<generic<T, N>> {
    static constexpr unsigned width = N;
    using scalar_type = T;
    using vector_type = std::array<T, N>;
};

template <typename T, unsigned N>
struct generic: fallback<generic<T, N>> {
    using array = std::array<T, N>;

    static void copy_to(array v, T* p) {
        std::copy(std::begin(v), std::end(v), p);
    }
    static array copy_from(const T* p) {
        array v;
        std::copy(p, p+N, v.data());
        return v;
    }
    static T element(array v, unsigned i) {
        return v[i];
    }
    static void set_element(array& v, unsigned i, const T& x) {
        v[i] = x;
    }
};

} // namespace tinysimd
