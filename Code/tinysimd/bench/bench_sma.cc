#include <memory>
#include <random>

#include <benchmark/benchmark.h>
#include <tinysimd/simd.h>

#define N 32768

[[gnu::noinline]]
void sma(double* __restrict out, double k, const double* a, const double* b) {
    for (unsigned i = 0; i<N; ++i) {
        out[i] = k*a[i] + b[i];
    }
}

[[gnu::noinline]]
void sma_simd(double* __restrict c, double k, const double* a, const double* b) {
    using namespace tinysimd;
    using vdouble = simd<double, 4, abi::default_abi>;

    for (unsigned i = 0; i<N; i += vdouble::width) {
        vdouble va(a+i), vb(b+i);
        vdouble vc = k*va + vb;
        vc.copy_to(c+i);
    }
}

std::unique_ptr<double[]> zero_array() {
    return std::unique_ptr<double[]>(new double[N]());
}

std::unique_ptr<double[]> random_array() {
    std::minstd_rand R;
    std::uniform_real_distribution<double> U;

    std::unique_ptr<double[]> p(new double[N]);
    std::generate(p.get(), p.get()+N, [&] { return U(R); });
    return p;
}

void bench_sma(benchmark::State& state) {
    auto a = random_array();
    auto b = random_array();
    auto c = zero_array();

    for (auto _: state) {
        sma(c.get(), 2.1, a.get(), b.get());
    }
}

void bench_sma_simd(benchmark::State& state) {
    auto a = random_array();
    auto b = random_array();
    auto c = zero_array();

    for (auto _: state) {
        sma_simd(c.get(), 2.1, a.get(), b.get());
    }
}

BENCHMARK(bench_sma);
BENCHMARK(bench_sma_simd);
BENCHMARK_MAIN();
