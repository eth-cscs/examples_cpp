#include <vector>
#include <iostream>
#include <algorithm>
#include <array>

int main(){
    using type = std::array<int,1000>;
    type t{1};
    std::vector< type > l_(10);

    for(auto i=l_.begin(); l_.begin() != l_.end() ; i++){
        l_.insert(i, t);
    }
}
