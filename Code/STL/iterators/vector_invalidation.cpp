#include <vector>
#include <list>
#include <iostream>
#include <algorithm>

int main(){
    int t=0;
    // std::vector< int > l_(10);
    // for(auto i=l_.begin(); i != l_.end() ; i++){
    //     l_.insert(i, t);
    // }
    std::list< int > l_(10);
    for(auto i=l_.begin(); i != l_.end() ; i++){
        l_.insert(i, t);
    }
    std::cout<<l_.size()<<"\n";
}
