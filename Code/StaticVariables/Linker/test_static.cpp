/**
   Test to be compiled either
   in a single translation unit
   g++ init_static.cpp test_static.cpp
   or with dynamic linking:
   g++ -c init_static.cpp -fPIC -o libs.o; g++ -shared -o libs.so libs.o;  g++ test_static.cpp -O3 -L. libs.so
   or with static linking:
   g++ -c init_static.cpp -o libs.o; ar rvs libs.a libs.o;  g++ test_static.cpp -O3 -L. libs.a
*/

#include <iostream>
#include "init_static.hpp"

int main()
{
    // std::cout<<register_product<float>::reg<<register_product<double>::reg<<"\n";
    // register_product<float>::reg;
    // register_product<double>::reg;
}
