#include <tinysimd/simd.h>

// scalar multiply vector add

#define N 32768

void mul_indexed(double* __restrict c, const int* index, const double* a, const double* b) {
    for (unsigned i = 0; i<N; ++i) {
        c[i] = a[index[i]] * b[index[i]];
    }
}

using namespace tinysimd;

void mul_indexed_avx2(double* __restrict c, const int* index, const double* a, const double* b) {
    using vdouble = simd<double, 4, abi::avx2>;
    using vint = simd<int, 4, abi::avx2>;

    for (unsigned i = 0; i<N; i += 4) {
        vint vi(index+i);
        vdouble vc = vdouble(indirect(a, vi))*vdouble(indirect(b, vi));
        vc.copy_to(c+i);
    }
}
