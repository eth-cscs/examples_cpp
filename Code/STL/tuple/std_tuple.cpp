#include <tuple>
#include <iostream>

int main(){
    auto t_=std::make_tuple( std::string("my string"), 1.1, 'b');
    std::cout<<std::get<std::string>(t_)<<"\n";
}
