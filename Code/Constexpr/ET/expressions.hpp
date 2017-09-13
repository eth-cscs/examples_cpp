#pragma once
#include <type_traits>

#include <iostream>
#include <string>

template <typename> struct expr_derivative;
template <typename, typename> struct expr_plus;
template <typename, typename> struct expr_times;

#include "constant.hpp"
#include "expr_derivative.hpp"
#include "expr_plus.hpp"
#include "expr_times.hpp"
#include "p.hpp"
