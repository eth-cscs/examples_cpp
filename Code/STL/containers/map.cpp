#include <map>
#include <iostream>

int main(){
    std::map< std::string, double > m_;

    m_.insert(std::make_pair("first", 0.));
    m_.insert(std::make_pair("second", 1.));
    m_.insert(std::make_pair("third", 1.));
    m_.insert(std::make_pair("third", 10.));

    double val=m_.find("third")->second;
    std::cout<<val<<"\n";
    std::cout<<"size: "<<m_.size()<<"\n";
}
