#include <iterator>
#include <algorithm>
#include <numeric>

#include <gtest/gtest.h>
#include <tinysimd/simd.h>

#include "unit_common.h"

using helpers::sequence_equal;
using helpers::fill_zero;

template <typename X> struct tinysimd_basic: public ::testing::Test {};
TYPED_TEST_SUITE_P(tinysimd_basic);

TYPED_TEST_P(tinysimd_basic, copy_and_assign) {
    using namespace tinysimd;

    using vec = TypeParam;
    using scalar = typename vec::scalar_type;
    constexpr unsigned width = vec::width;

    scalar in[width], out[width];
    generate_test_data(in);

    vec v1(in);
    fill_zero(out);
    v1.copy_to(out);
    EXPECT_PRED2(sequence_equal, in, out);

    vec v2;
    v2 = v1;
    fill_zero(out);
    v2.copy_to(out);
    EXPECT_PRED2(sequence_equal, in, out);

    vec v3(v1);
    fill_zero(out);
    v3.copy_to(out);
    EXPECT_PRED2(sequence_equal, in, out);
}

TYPED_TEST_P(tinysimd_basic, arithmetic) {
    using namespace tinysimd;

    using vec = TypeParam;
    using scalar = typename vec::scalar_type;
    constexpr unsigned width = vec::width;

    scalar in1[width], in2[width], in3[width], out[width], check[width];
    generate_test_data(in1);
    generate_test_data(in2);
    generate_test_data(in3);

    vec v1(in1), v2(in2), v3(in3), vc;

    for (unsigned i = 0; i<width; ++i) check[i] = in1[i]+in2[i];
    fill_zero(out);
    (v1+v2).copy_to(out);
    EXPECT_PRED2(sequence_equal, check, out);

    fill_zero(out);
    vc = v1;
    vc += v2;
    vc.copy_to(out);
    EXPECT_PRED2(sequence_equal, check, out);

    for (unsigned i = 0; i<width; ++i) check[i] = in1[i]*in2[i];
    fill_zero(out);
    (v1*v2).copy_to(out);
    EXPECT_PRED2(sequence_equal, check, out);

    fill_zero(out);
    vc = v1;
    vc *= v2;
    vc.copy_to(out);
    EXPECT_PRED2(sequence_equal, check, out);

    for (unsigned i = 0; i<width; ++i) check[i] = std::fma(in1[i], in2[i], in3[i]);
    fill_zero(out);
    fma(v1, v2, v3).copy_to(out);
    EXPECT_PRED2(sequence_equal, check, out);

    scalar hsum = std::accumulate(in1, in1+width, scalar{0});
    EXPECT_EQ(hsum, reduce(v1));
}

TYPED_TEST_P(tinysimd_basic, element) {
    using namespace tinysimd;

    using std::begin;
    using std::end;

    using vec = TypeParam;
    using scalar = typename vec::scalar_type;
    constexpr unsigned width = vec::width;

    scalar in[width], out[width], check[width];
    generate_test_data(in);

    for (unsigned i = 0; i<width; ++i) {
        EXPECT_EQ(in[i], vec(in)[i]);
    }

    for (unsigned i = 0; i<width; ++i) {
        std::copy(begin(in), end(in), begin(check));
        check[i] = 123.;

        vec v(in);
        v[i] = 123.;
        v.copy_to(out);

        EXPECT_PRED2(sequence_equal, check, out);

        (v[i] = 234) = 345;
        v.copy_to(out);
        check[i] = 345.;

        EXPECT_PRED2(sequence_equal, check, out);
    }
}

REGISTER_TYPED_TEST_SUITE_P(tinysimd_basic, copy_and_assign, arithmetic, element);

typedef ::testing::Types<
    tinysimd::simd<double, 4, tinysimd::abi::avx2>,
    tinysimd::simd<int,    4, tinysimd::abi::avx2>,
    tinysimd::simd<float,  2, tinysimd::abi::generic>
> simd_test_types;
INSTANTIATE_TYPED_TEST_SUITE_P(S, tinysimd_basic, simd_test_types);
