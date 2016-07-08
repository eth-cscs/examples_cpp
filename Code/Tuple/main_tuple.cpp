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

//solution to exercice 3
#include "value_tuple_mixed.hpp"
#include "integer_tuple_mixed.hpp"

#include <iostream>
#include <string>

struct pi {
    double m_value;

    constexpr pi()
        : m_value{3.1415926/4.0}
    {}

    constexpr pi(int n)
        : m_value(3.1415926/4.0*n)
    {}

    operator double() const {
        return m_value;
    }
};

std::ostream& operator<<(std::ostream& s, pi p) {
    return s << static_cast<double>(p);
}

template<short T, short U>
struct pair{
    static constexpr short first=T;
    static constexpr short second=U;
};

extern constexpr value_tuple<int, char, pi> const c_tuple_(pos<1>(3), pos<3>(10));

int main(){

    //run-time instance
    volatile double mut_val=-3.1415926;

    value_tuple<bool, char, double, int, pi> tuple(pos<1>(false),
                                               pos<3>(mut_val),
                                               pos<2>('m'));
    std::cout << tuple.get<1>() << " "
              << tuple.get<2>() << " "
              << tuple.get<3>() << " "
              << tuple.get<4>() << " "
              << tuple.get<5>() << " "
              << std::endl;

    value_tuple<bool, char, double, pi> default_tuple;
    std::cout << default_tuple.get<1>() << " "
              << default_tuple.get<2>() << " "
              << default_tuple.get<3>() << " "
              << default_tuple.get<4>() << " "
              << std::endl;


    constexpr value_tuple<bool, char, double, int> ctuple(pos<1>(false), pos<3>(3.14), pos<2>('m'));
    static_assert(ctuple.get<1>()==false, "error");
    static_assert(ctuple.get<2>()=='m', "error");
    static_assert(ctuple.get<3>()==3.14, "error");
    static_assert(ctuple.get<4>()==int(), "error");
    //    static_assert(c_tuple.get<4>()=='b', "error");  // This trigger an error


    //exercice: make the following tuple compile
    value_tuple<bool, short, std::string> tuple2(pos<1>(false), pos<2>(4), pos<3>(std::string("pink pig")));

    tuple2.set<3>(std::string("black dog"));

    std::cout<<tuple2.get<3>()<<std::endl;
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
    //implement an interface which mixes run-time and compile-time components in an offset-tuple
    //using tuple_t = offset_tuple<int, 5>
    //using alias<pos<1>, 5> = new_tuple_t;
    //new_tuple_t(pos<4>(3));

    detail_::integer_tuple_mixed< make_value_tuple<int,4>, pair<5, 44> > tmp;

    static_assert(detail_::get<5>(tmp)==44, "error");
    static_assert(tmp.get<5>()==44, "error");


    //the interface for generic tuple (not only integers) becomes a bit cumbersome
    detail_::value_tuple_mixed< make_value_tuple<int,4>, const value_tuple<int, char, pi>, c_tuple_> tmp2;

    static_assert(tmp2.get<3>().m_value==pi(10).m_value, "error");
}
