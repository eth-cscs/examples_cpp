#include <set>
#include <iostream>

int main(){
    std::set< double > m_;

    m_.insert( 0. );
    m_.insert( 1. );
    m_.insert( 1. );

    auto val=m_.find(1.);

    std::cout<<*val<<"\n";
    std::cout<<"size: "<<m_.size()<<"\n";
}
