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

#include "my_tuple.hpp"

//solution to exercice 2
#include "make_tuple.hpp"

#include <iostream>
#include <string>

int main(){

    //run-time instance
    volatile double mut_val=13;
    auto arg1=arg<1>(false);
    auto arg2=arg<2>(4);
    auto arg3=arg<3>(mut_val);
    my_tuple<bool, short, double> tuple(arg1, arg2, arg3);

    //compile-time instance
    constexpr my_tuple<int, double, char> c_tuple(arg<3>('b'), arg<1>(-3), arg<2>(1.5));
    static_assert(c_tuple.get<1>()==-3, "error");
    static_assert(c_tuple.get<2>()==1.5, "error");
    static_assert(c_tuple.get<3>()=='b', "error");
    //    static_assert(c_tuple.get<4>()=='b', "error");  // This trigger an error

    //exercice: make the following tuple compile
    my_tuple<bool, short, std::string> tuple2(arg<1>(false), arg<2>(4), arg<3>(std::string("pink pig")));

    //advanced exercice:
    //implement a tuple which expands the interface make_tuple<type, 5> to
    //my_tuple<type, type, type, type, type>
    make_tuple<int, 5> new_tuple(arg<5>(66), arg<4>(55), arg<3>(44), arg<2>(33),arg<1>(22));

    std::cout << new_tuple.get<1>() << " "
              << new_tuple.get<2>() << " "
              << new_tuple.get<3>() << " "
              << new_tuple.get<4>() << " "
              << new_tuple.get<5>() << " "
              << std::endl;
    //very advanced exercice (probably not a good idea):
    //implement an interface which mixes run-time and compile-time components in an offset-tuple
    //using tuple_t = offset_tuple<int, 5>
    //using alias<arg<1>, 5> = new_tuple_t;
    //new_tuple_t(arg<4>(3));

    return 0;

}
