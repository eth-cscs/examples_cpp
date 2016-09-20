#include <iostream>
#include <vector>
#include <tuple>

constexpr int f1(std::vector<int> const& v_){ return v_.size();}

template<typename ... T>
constexpr auto f2(std::tuple<T...> const& t_){ return std::get<2>(t_);}

template<typename ... T>
constexpr auto f3(std::tuple<T...> const& t_){
    bool cond=std::get<2>(t_)<std::get<1>(t_);
    if(cond)
        return std::get<2>(t_);
    else
        return std::get<1>(t_);
}

int main(){

    std::vector<int> t_{0,1,2,3,4};
    std::cout<<f1(t)<<"\n";
    auto t=std::make_tuple(1,2,3,4);
    std::cout<<f2(t)<<"\n";
    std::cout<<f3(t)<<"\n";
}
