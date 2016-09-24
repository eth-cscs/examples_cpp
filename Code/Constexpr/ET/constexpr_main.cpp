#include <iostream>

int main(int argc , char** argv){

    constexpr auto expr = x*x+x;

    static_assert(expr(5.) == 30);
}
