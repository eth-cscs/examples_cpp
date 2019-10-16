#pragma once

// Common small utilites for unit tests and benchmarks.

#include <iterator>
#include <algorithm>
#include <random>
#include <stdexcept>

namespace helpers {

// Randomly sample without replacement from [0, upto) in-place using reservoir sampling,
// into a random-access container.

template <typename Rng, typename RAContainer>
void reservoir_sample_upto(Rng& R, RAContainer& values, std::size_t upto) {
    using std::begin;
    using std::end;

    std::size_t n = std::distance(begin(values), end(values));
    if (n>=upto) throw std::out_of_range("upto too small");

    std::iota(begin(values), end(values), 0);

    std::uniform_real_distribution<float> U;
    std::uniform_int_distribution<unsigned> S(0u, n-1);

    const float select_p = (float)n/upto;
    for (std::size_t i = n; i<upto; ++i) {
        if (U(R)>select_p) values[S(R)] = i;
    }
}

// Functional equality comparison between two containers/sequences.

static auto sequence_equal = [](const auto& s1, const auto &s2) {
    using std::begin;
    using std::end;

    return std::equal(begin(s1), end(s1), begin(s2), end(s2));
};

// Fill container with zero.

template <typename Container>
void fill_zero(Container& c) {
    using std::begin;
    using std::end;
    using value_type = std::decay_t<decltype(*begin(c))>;

    std::fill(begin(c), end(c), value_type(0));
}

} // namespace helpers

