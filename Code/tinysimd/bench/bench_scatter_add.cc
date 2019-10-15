#include <memory>
#include <random>

#include <iostream>
#include <vector>

#include <benchmark/benchmark.h>
#include <tinysimd/simd.h>
#include "helpers.h"

// Benchmark: scatter-add of values computed from a small kernel.
//     data[index[i]] += kernel(a[i]).
//
// Two scenarios:
// 1. 'dense': 10x indices as data values; indices monotonically increasing.
// 2. 'sparse': 10x data values as indices: indices monotonically increasing and distinct.
constexpr float dense_ratio = 10.f;
constexpr float sparse_ratio = 0.1f;

using namespace tinysimd;


// Polynomial evaluation for scalars or simd values.
template <typename V>
V kernel(V x) {
    return 5+x*(1+x*(2+x*3));
}

[[gnu::noinline]]
void scatter_add(double* __restrict out, unsigned na, const double* a, const int* index) {
    for (unsigned i = 0; i<na; ++i) {
        out[index[i]] += kernel(a[i]);
    }
}

template <unsigned width>
[[gnu::noinline]]
void scatter_add_simd(double* __restrict out, unsigned na, const double* a, const int* index, constraint c = constraint::none) {
    using vdouble = simd<double, width>;
    using vint = simd<int, width>;

    for (unsigned i = 0; i<na; i += width) {
        vdouble va(a+i);
        vint vindex(index+i);

        indirect(out, vindex, c) += kernel(va);
    }
}

template <unsigned width>
[[gnu::noinline]]
void scatter_add_simd_subset(double* __restrict out, unsigned na, const double* a,
                                const int* offset, const int* index, constraint c) {
    using vdouble = simd<double, width>;
    using vint = simd<int, width>;

    for (unsigned i = 0; i<na; ++i) {
        vdouble va(a+offset[i]);
        vint vindex(index+offset[i]);

        indirect(out, vindex, c) += va*va;
    }
}

std::vector<double> random_array(unsigned n) {
    std::minstd_rand R; // Same sequence each call.
    std::uniform_real_distribution<double> U;

    std::vector<double> v(n);
    std::generate(v.begin(), v.end(), [&] { return U(R); });
    return v;
}

std::vector<int> random_independent_index(unsigned n, unsigned upto) {
    std::minstd_rand R; // Same sequence each call.

    std::vector<int> indices(n);
    helpers::reservoir_sample_upto(R, indices, upto);
    return indices;
}

std::vector<int> random_monotonic_index(unsigned n, unsigned upto) {
    std::minstd_rand R; // Same sequence each call.
    std::uniform_int_distribution<int> U(0,upto-1);

    std::vector<int> indices(n);
    std::generate(indices.begin(), indices.end(), [&] { return U(R); });
    std::sort(indices.begin(), indices.end());
    return indices;
}

struct test_dataset {
    std::vector<double> out;
    std::vector<double> a;
    std::vector<int> index;
};

template <unsigned width>
test_dataset generate_test_data(float density, bool indep) {
    unsigned index_size = 8192;
    unsigned data_size = index_size/density;
    data_size = width*(1+(data_size-1)/width);

    test_dataset dset;
    dset.out = random_array(data_size);
    dset.a = random_array(index_size);
    dset.index = indep? random_independent_index(index_size, data_size): random_monotonic_index(index_size, data_size);
    return dset;
}

void dense_scatter_add(benchmark::State& state) {
    test_dataset D = generate_test_data<4>(dense_ratio, false);

    for (auto _: state) {
        scatter_add(D.out.data(), D.a.size(), D.a.data(), D.index.data());
    }
}

void dense_scatter_add_simd(benchmark::State& state) {
    test_dataset D = generate_test_data<4>(dense_ratio, false);

    for (auto _: state) {
        scatter_add_simd<4>(D.out.data(), D.a.size(), D.a.data(), D.index.data(), constraint::monotonic);
    }
}

void dense_scatter_add_preconstrain(benchmark::State& state) {
    constexpr unsigned width = 4;
    test_dataset D = generate_test_data<4>(dense_ratio, false);

    std::vector<int> constant_offsets;
    std::vector<int> monotone_offsets;

    for (unsigned i = 0; i<D.index.size(); i+=width) {
        if (D.index[i]==D.index[i+width-1]) constant_offsets.push_back(i);
        else monotone_offsets.push_back(i);
    }

    for (auto _: state) {
        scatter_add_simd_subset<width>(D.out.data(), constant_offsets.size(), D.a.data(), constant_offsets.data(), D.index.data(), constraint::constant);
        scatter_add_simd_subset<width>(D.out.data(), monotone_offsets.size(), D.a.data(), monotone_offsets.data(), D.index.data(), constraint::monotonic);
    }
}

void sparse_scatter_add(benchmark::State& state) {
    test_dataset D = generate_test_data<4>(sparse_ratio, true);

    for (auto _: state) {
        scatter_add(D.out.data(), D.a.size(), D.a.data(), D.index.data());
    }
}

void sparse_scatter_add_simd(benchmark::State& state) {
    test_dataset D = generate_test_data<4>(sparse_ratio, true);

    for (auto _: state) {
        scatter_add_simd<4>(D.out.data(), D.a.size(), D.a.data(), D.index.data(), constraint::monotonic);
    }
}


BENCHMARK(dense_scatter_add);
BENCHMARK(dense_scatter_add_simd);
BENCHMARK(dense_scatter_add_preconstrain);
BENCHMARK(sparse_scatter_add);
BENCHMARK(sparse_scatter_add_simd);
BENCHMARK_MAIN();
