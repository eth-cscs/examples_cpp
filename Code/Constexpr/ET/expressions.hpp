#pragma once
#include <type_traits>

#include <iostream>
#include <string>

template <typename> struct expr_derivative;
template <typename, typename> struct expr_plus;
template <typename, typename> struct expr_times;

#include "constant.hpp"
#include "p.hpp"

#if __cplusplus >= 201402L
#include "expr_derivative.hpp"
#include "expr_plus.hpp"
#include "expr_times.hpp"
#else
#pragma message("Compiling with C++11")
#include "expr_derivative_cxx11.hpp"
#include "expr_plus_cxx11.hpp"
#include "expr_times_cxx11.hpp"
#endif
