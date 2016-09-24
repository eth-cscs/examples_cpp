#include <iostream>

int main(){
    constexpr my_tuple<int, double> t_(1,3.4);
    std::cout<<get<1>(t_)<<"\n";
    static_assert(get<1>(t_)==3.4);
}
