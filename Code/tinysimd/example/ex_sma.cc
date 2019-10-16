#include <tinysimd/simd.h>

// scalar multiply vector add

#define N 32768

void sma(double* __restrict c, double k, const double* a, const double* b) {
    for (unsigned i = 0; i<N; ++i) {
        c[i] = k*a[i] + b[i];
    }
}

using namespace tinysimd;

void sma_avx2(double* __restrict c, double k, const double* a, const double* b) {
    using vdouble = simd<double, 4, abi::avx2>;

    for (unsigned i = 0; i<N; i += vdouble::width) {
        vdouble va(a+i), vb(b+i);
        vdouble vc = k*va + vb;
        vc.copy_to(c+i);
    }
}


void sma_generic1(double* __restrict c, double k, const double* a, const double* b) {
    using vdouble = simd<double, 1, abi::generic>;

    for (unsigned i = 0; i<N; i += vdouble::width) {
        vdouble va(a+i), vb(b+i);
        vdouble vc = k*va + vb;
        vc.copy_to(c+i);
    }
}

void sma_generic4(double* __restrict c, double k, const double* a, const double* b) {
    using vdouble = simd<double, 4, abi::generic>;

    for (unsigned i = 0; i<N; i += vdouble::width) {
        vdouble va(a+i), vb(b+i);
        vdouble vc = k*va + vb;
        vc.copy_to(c+i);
    }
}
