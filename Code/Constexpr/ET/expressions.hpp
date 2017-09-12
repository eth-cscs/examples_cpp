#pragma once
#include <type_traits>

#include <string>
#include <iostream>

template <typename >
struct expr_derivative;
template <typename , typename >
struct expr_plus;
template <typename , typename >
struct expr_times;

#include "constant.hpp"
#include "p.hpp"
#include "expr_times.hpp"
#include "expr_plus.hpp"
#include "expr_derivative.hpp"
