#include <list>
#include <iostream>
#include <algorithm>
#include <array>

int main(){
    std::list< int > l_(1e5);

    for(auto&& i=l_.begin(); i != l_.end(); i++){
        l_.insert(i, 8);
    }
}
