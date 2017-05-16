#include <vector>
#include <iostream>
#include <iterator>

int main(){

    std::vector<int> v{8,8};
    auto i = std::inserter(v, v.begin());
    for(int j=0; j<5; j++, i)
        i=j;

    for(int j : v)
        std::cout<<j<<" ";
    std::cout<<"\n";
}
