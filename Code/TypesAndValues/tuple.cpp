#include <tuple>
#include <string>
#include <type_traits>
#include <iostream>

int main() {
    std::tuple<int, std::string, float> t(10,"A",3.14);

    auto tuple = std::make_tuple("Hello", 42, std::string("World"));
    static_assert(std::is_same<std::tuple_element<0,decltype(tuple)>::type, const char*>::value, "");
    static_assert(std::is_same<std::tuple_element<1,decltype(tuple)>::type, int>::value, "");
    static_assert(std::is_same<std::tuple_element<2,decltype(tuple)>::type, std::string>::value, "");

    const char* ptr;
    int x;
    std::string str;
    std::tie(ptr, x, str) = tuple;
    std::cout << ptr << x << str <<"\n";
}
