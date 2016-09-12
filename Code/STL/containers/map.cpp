#include <map>
#include <iostream>

int main(){
    std::map< std::string, double > m_;
    m_.emplace("first", 0.);
    m_.emplace("second", 1.);
    m_.emplace("third", 1.);
    double val=m_.at("third");
    std::cout<<val<<"\n";
    std::cout<<"size: "<<m_.size()<<"\n";
}
