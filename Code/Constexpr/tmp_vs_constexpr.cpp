#include <iostream>
//run:
//time g++ -O3 example_00.cpp -ftemplate-depth=100000 -fconstexpr-depth=100000
template <int I>
struct sum{ // template recursion
    static const long int value=I+sum<I-1>::value;
};

template <>
struct sum<1>{
    static const long int value=1;
};

constexpr int sum2(int id){ // regular recursion
    return id>1 ? id+sum2(id-1) : id;
};

int main(){
    static_assert(sum<100>::value > 0, "error");
    static_assert(sum2(100) > 0, "error");
    std::cout<<sum2(100)<<"\n";
}

// see :
// https://gcc.godbolt.org/#compilers:!((compiler:g62,options:'-std%3Dc%2B%2B11+-O3++-fconstexpr-depth%3D1000',source:'constexpr+%0A++int+sum2(int+id)%7B%0A++++return+id%3E1+%3F+id%2Bsum2(id-1)+:+id%3B%0A%7D%3B%0A%0Aint+main()%7B%0A++//constexpr+int+ret%3Dsum2(100)%3B%0A++//return+ret%3B%0A++return+sum2(100)%3B%0A%7D%0A')),filterAsm:(commentOnly:!t,directives:!t,labels:!t),version:3
