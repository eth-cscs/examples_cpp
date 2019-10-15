#pragma once

#include <immintrin.h>
#include <cstdint>
#include <tinysimd/common.h>

namespace tinysimd {

namespace abi {

template <typename T, unsigned N> struct avx2 { using type = void; };

} // namespace abi


#if defined(__AVX2__) && defined(__FMA__)

struct avx2_double4;
template <> struct simd_traits<avx2_double4> {
    static constexpr unsigned width = 4;
    using scalar_type = double;
    using vector_type = __m256d;
};

struct avx2_int4;
template <> struct simd_traits<avx2_int4> {
    static constexpr unsigned width = 4;
    using scalar_type = std::int32_t;
    using vector_type = __m128i;
};

namespace abi {

template <> struct avx2<int, 4> { using type = avx2_int4; };
template <> struct avx2<double, 4> { using type = avx2_double4; };

} // namespace abi

struct avx2_double4: fallback<avx2_double4> {
    static void copy_to(__m256d v, double* p) {
        _mm256_storeu_pd(p, v);
    }
    static __m256d copy_from(const double* p) {
        return _mm256_loadu_pd(p);
    }
    static __m256d broadcast(double v) {
        return _mm256_set1_pd(v);
    }
    static __m256d add(__m256d a, __m256d b) {
        return _mm256_add_pd(a, b);
    }
    static __m256d mul(__m256d a, __m256d b) {
        return _mm256_mul_pd(a, b);
    }
    static __m256d fma(__m256d u, __m256d v, __m256d w) {
        return _mm256_fmadd_pd(u, v, w);
    }
    static double reduce_add(__m256d a) {
        // add [a3|a2|a1|a0] to [a1|a0|a3|a2]
        __m256d b = add(a, _mm256_permute2f128_pd(a, a, 0x01));
        // add [b3|b2|b1|b0] to [b2|b3|b0|b1]
        __m256d c = add(b, _mm256_permute_pd(b, 0x05));

        return element(c, 0);
    }

    using fallback<avx2_double4>::gather;
    static __m256d gather(tag<avx2_int4>, const double* p, __m128i index) {
        return _mm256_i32gather_pd(p, index, 8);
    }
};

struct avx2_int4: fallback<avx2_int4> {
    using i32 = std::int32_t;

    static void copy_to(__m128i v, i32* p) {
        _mm_storeu_si128((__m128i*)p, v);
    }
    static __m128i copy_from(const i32* p) {
        return _mm_loadu_si128((const __m128i*)p);
    }
    static __m128i broadcast(i32 v) {
        return _mm_set1_epi32(v);
    }
    static __m128i add(__m128i a, __m128i b) {
        return _mm_add_epi32(a, b);
    }
    static __m128i mul(__m128i a, __m128i b) {
        return _mm_mullo_epi32(a, b);
    }
    static __m128i fma(__m128i u, __m128i v, __m128i w) {
        return add(mul(u, v), w);
    }
    static i32 reduce_add(__m128i a) {
        // Add [a3|a2|a1|a0] to [a2|a3|a0|a1]
        __m128i b = add(a, _mm_shuffle_epi32(a, 0xb1));
        // Add [b3|b2|b1|b0] to [b1|b0|b3|b2]
        __m128i c = add(b, _mm_shuffle_epi32(b, 0x4e));
        return element(c, 0);
    }

    using fallback<avx2_int4>::gather;
    static __m128i gather(tag<avx2_int4>, const i32* p, __m128i index) {
        return _mm_i32gather_epi32(p, index, 4);
    }
};

#endif // defined(__AVX2__) && defined(__FMA__)

} // namespace tinysimd
