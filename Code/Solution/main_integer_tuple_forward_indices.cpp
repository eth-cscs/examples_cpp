/**
   We implement a modified version of std::tuple, in which we can specify the members out of order,
   we try to show also the power of constexprness and variadic templates.

   Prerequisites:
   good understanding of
   * variadic template
   * constexpr keyword
   * integer_sequence
   * template recursion
*/

#include "integer_tuple_forward_indices.hpp"


#include <iostream>
#include <string>


int main(){


    integer_tuple<4> tuple(pos<1>(-3), pos<3>(7), pos<4>(19));
    std::cout << tuple.get<1>() << " "
              << tuple.get<2>() << " "
              << tuple.get<3>() << " "
              << tuple.get<4>() << " "
              << std::endl;

    integer_tuple<4> default_tuple;
    std::cout << default_tuple.get<1>() << " "
              << default_tuple.get<2>() << " "
              << default_tuple.get<3>() << " "
              << default_tuple.get<4>() << " "
              << std::endl;


    constexpr integer_tuple<4> ctuple(pos<1>(1), pos<3>(3), pos<2>(2));
    static_assert(ctuple.get<1>()==1, "error");
    static_assert(ctuple.get<2>()==2, "error");
    static_assert(ctuple.get<3>()==3, "error");
    static_assert(ctuple.get<4>()==int(), "error");
    //    static_assert(c_tuple.get<4>()=='b', "error");  // This trigger an error


    return 0;

}
