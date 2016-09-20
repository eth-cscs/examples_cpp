#include <iostream>
template <typename Ret, typename ... T>
constexpr bool is_constexpr(Ret(f)(T ...), T ... t_){
    return noexcept (f(t_ ...));
}

constexpr auto my_func(int a, int b, double c){
    return a+b+c;
}

auto my_other_func(int a, int b, double c){
    return a+b+c;
}


int main(){

    constexpr int first=1;
    constexpr int second=2;
    constexpr double third=3.5;

    auto f1=&my_other_func;
    constexpr auto f2=&my_func;
    // bool a= noexcept(my_other_func( 1, 2, 3.5));
    // bool b= noexcept(my_func( first, second, third));
    bool a= is_constexpr(f1, 1, 2, 3.5);
    bool b= is_constexpr(f2, first, second, third);
    std::cout<<a<<"=false"<<"\n";
    std::cout<<b<<"=true"<<"\n";
}
