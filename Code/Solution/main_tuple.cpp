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

#include "value_tuple.hpp"

//solution to exercice 2
#include "make_value_tuple.hpp"

#include <iostream>
#include <string>

int main(){

    //run-time instance
    volatile double mut_val=13;
    value_tuple<bool, short, double> tuple(pos<1>(false), pos<2>(4), pos<3>(mut_val));

    //compile-time instance
    constexpr value_tuple<int, double, char> c_tuple(pos<3>('b'), pos<1>(-3), pos<2>(1.5));
    static_assert(c_tuple.get<1>()==-3, "error");
    static_assert(c_tuple.get<2>()==1.5, "error");
    static_assert(c_tuple.get<3>()=='b', "error");
    //    static_assert(c_tuple.get<4>()=='b', "error");  // This trigger an error

    //exercice: make the following tuple compile
    value_tuple<bool, short, std::string> tuple2(pos<1>(false), pos<2>(4), pos<3>(std::string("pink pig")));

    //advanced exercice:
    //implement a tuple which expands the interface make_tuple<type, 5> to
    //value_tuple<type, type, type, type, type>
    make_value_tuple<int, 5> new_tuple(pos<5>(66), pos<4>(55), pos<3>(44), pos<2>(33),pos<1>(22));

    std::cout << new_tuple.get<1>() << " "
              << new_tuple.get<2>() << " "
              << new_tuple.get<3>() << " "
              << new_tuple.get<4>() << " "
              << new_tuple.get<5>() << " "
              << std::endl;
    //very advanced exercice (probably not a good idea):
    //implement an interface which mixes run-time and compile-time compmnents in an offset-tuple
    //using tuple_t = offset_tuple<int, 5>
    //using alias<pos<1>, 5> = new_tuple_t;
    //new_tuple_t(pos<4>(3));

    return 0;

}
