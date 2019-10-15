#include <string>

#include <gtest/gtest.h>
#include <tinysimd/simd.h>

#include "unit_common.h"

using helpers::sequence_equal;
using helpers::fill_zero;

template <typename X> struct tinysimd_indirect: public ::testing::Test {};
TYPED_TEST_SUITE_P(tinysimd_indirect);

TYPED_TEST_P(tinysimd_indirect, gather) {
    using namespace tinysimd;

    using vvec = typename TypeParam::simd_value;
    using ivec = typename TypeParam::simd_index;

    using scalar = typename vvec::scalar_type;
    using index = typename ivec::scalar_type;

    constexpr unsigned width = vvec::width;
    static_assert(width==ivec::width, "mismatched SIMD types");

    constexpr unsigned data_width = width*2.5;
    scalar data[width*3];
    generate_test_data(data);

    index indices[width];
    scalar out[width], check[width];
    constraint c = constraint::none;

    // Run each constraint over a number of randomly-generated index sets:
    for (auto c: {constraint::none, constraint::constant, constraint::contiguous,
                  constraint::monotonic, constraint::independent}) {
        using std::to_string;

        for (unsigned iter = 0; iter<10; ++iter) {
            SCOPED_TRACE("constraint::"+to_string(c)+" iteration "+to_string(iter));
            generate_constrained_indices(indices, data_width, c);

            for (unsigned i = 0; i<width; ++i) check[i] = data[indices[i]];
            vvec(indirect(data, ivec(indices), c)).copy_to(out);
            EXPECT_PRED2(sequence_equal, check, out);
        }
    }
}

TYPED_TEST_P(tinysimd_indirect, scatter) {
    using namespace tinysimd;

    using vvec = typename TypeParam::simd_value;
    using ivec = typename TypeParam::simd_index;

    using scalar = typename vvec::scalar_type;
    using index = typename ivec::scalar_type;

    constexpr unsigned width = vvec::width;
    static_assert(width==ivec::width, "mismatched SIMD types");

    constexpr unsigned data_width = width*2.5;
    scalar data[data_width], out[data_width], check[data_width];
    fill_zero(out);
    generate_test_data(data);

    scalar values[width];
    generate_test_data(values);
    vvec vval(values);

    index indices[width];
    constraint c = constraint::none;

    // Run each constraint over a number of randomly-generated index sets:
    for (auto c: {constraint::none, constraint::constant, constraint::contiguous,
                  constraint::monotonic, constraint::independent}) {
        using std::to_string;
        using std::begin;
        using std::end;

        for (unsigned iter = 0; iter<10; ++iter) {
            SCOPED_TRACE("constraint::"+to_string(c)+" iteration "+to_string(iter));
            generate_constrained_indices(indices, data_width, c);

            std::copy(begin(data), end(data), check);
            for (unsigned i = 0; i<width; ++i) check[indices[i]] = values[i];

            std::copy(begin(data), end(data), out);
            indirect(out, ivec(indices), c) = vval;
            EXPECT_PRED2(sequence_equal, check, out);
        }
    }
}

TYPED_TEST_P(tinysimd_indirect, scatter_add) {
    using namespace tinysimd;

    using vvec = typename TypeParam::simd_value;
    using ivec = typename TypeParam::simd_index;

    using scalar = typename vvec::scalar_type;
    using index = typename ivec::scalar_type;

    constexpr unsigned width = vvec::width;
    static_assert(width==ivec::width, "mismatched SIMD types");

    constexpr unsigned data_width = width*2.5;
    scalar data[data_width], out[data_width], check[data_width];
    fill_zero(out);
    generate_test_data(data);

    scalar values[width];
    generate_test_data(values);
    vvec vval(values);

    index indices[width];
    constraint c = constraint::none;

    // Run each constraint over a number of randomly-generated index sets:
    for (auto c: {constraint::none, constraint::constant, constraint::contiguous,
                  constraint::monotonic, constraint::independent}) {
        using std::to_string;
        using std::begin;
        using std::end;

        for (unsigned iter = 0; iter<10; ++iter) {
            SCOPED_TRACE("constraint::"+to_string(c)+" iteration "+to_string(iter));
            generate_constrained_indices(indices, data_width, c);

            std::copy(begin(data), end(data), check);
            for (unsigned i = 0; i<width; ++i) check[indices[i]] += values[i];

            std::copy(begin(data), end(data), out);
            indirect(out, ivec(indices), c) += vval;
            EXPECT_PRED2(sequence_equal, check, out);
        }
    }
}


REGISTER_TYPED_TEST_SUITE_P(tinysimd_indirect, gather, scatter, scatter_add);

template <typename SimdValue, typename SimdIndex>
struct simd_pair {
    using simd_value = SimdValue;
    using simd_index = SimdIndex;
};

typedef ::testing::Types<
    simd_pair<tinysimd::simd<double, 4, tinysimd::abi::avx2>,    tinysimd::simd<int, 4, tinysimd::abi::avx2>>,
    simd_pair<tinysimd::simd<int,    4, tinysimd::abi::avx2>,    tinysimd::simd<int, 4, tinysimd::abi::avx2>>,
    simd_pair<tinysimd::simd<float,  2, tinysimd::abi::generic>, tinysimd::simd<int, 2, tinysimd::abi::generic>>
> simd_test_types;
INSTANTIATE_TYPED_TEST_SUITE_P(S, tinysimd_indirect, simd_test_types);
