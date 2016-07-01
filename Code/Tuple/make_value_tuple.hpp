#pragma once
#include "value_tuple.hpp"

namespace detail_ {
template<typename Tuple, int N>
struct repeat_template{};

template<int Dim, typename First, typename ... T, int N>
struct repeat_template<sized_value_tuple<Dim, First, T ...>, N >{
    using type = typename repeat_template<sized_value_tuple<Dim+1, First, First, T ...>, N-1>::type;
};

template<int Dim, typename First, typename ... T>
struct repeat_template<sized_value_tuple<Dim, First, T ...>, 0 >{
    using type = sized_value_tuple<Dim, First, T ...>;
};
} //namespace detil_

template<typename T, int N>
using make_value_tuple = typename detail_::repeat_template<detail_::sized_value_tuple<1, T>, N-1 >::type;

//NOTE: linear complexity, can be improved
