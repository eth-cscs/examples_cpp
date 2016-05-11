#pragma once
#include <type_traits>

#include <string>
#include <iostream>

#include "expr_base.hpp"
#include "p.hpp"
#include "expr_plus.hpp"
#include "expr_derivative.hpp"

namespace expressions{

        /**
           Expressions defining the interface for specifiyng a given offset for a specified dimension
           \tparam Left: argument of type dimension<>::Index, specifying the offset in the given direction
        */
        template<typename Left>
        constexpr typename Left::super operator +(Left d1, int const&  offset) { return typename Left::super( offset );}

        template<typename Left>
        constexpr typename Left::super operator -(Left d1, int const&  offset) {return typename Left::super(-offset);}

    }//namespace expressions
