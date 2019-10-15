#include <tinysimd/simd.h>

#define N 8192

constexpr unsigned width = 4;

template <typename V>
V kernel(V x) {
    return 5+x*(1+x*(2+x*3));
}

void scatter_add(double* __restrict out, const double* a, const int* index) {
    for (unsigned i = 0; i<N; ++i) {
        out[index[i]] += kernel(a[i]);
    }
}

[[gnu::noinline]]
void scatter_add_simd(double* __restrict out, const double* a, const int* index) {
    using namespace tinysimd;
    using vdouble = simd<double, width, abi::avx2>;
    using vint = simd<int, width, abi::avx2>;

    for (unsigned i = 0; i<N; i += width) {
        vdouble va(a+i);
        vint vindex(index+i);

        indirect(out, vindex) += kernel(va);
    }
}

[[gnu::noinline]]
void scatter_add_simd_independent(double* __restrict out, const double* a, const int* index) {
    using namespace tinysimd;
    using vdouble = simd<double, width, abi::avx2>;
    using vint = simd<int, width, abi::avx2>;

    for (unsigned i = 0; i<N; i += width) {
        vdouble va(a+i);
        vint vindex(index+i);

        indirect(out, vindex, constraint::independent) += kernel(va);
    }
}
