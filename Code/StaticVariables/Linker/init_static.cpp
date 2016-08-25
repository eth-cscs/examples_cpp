#include "init_static.hpp"
#include <iostream>
template<>
bool register_product<double>::reg = [](){std::cout<<"initializing double\n"; return true;}();
template<>
bool register_product<float>::reg = [](){std::cout<<"initializing float\n"; return true;}();
