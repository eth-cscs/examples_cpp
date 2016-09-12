#include <vector>
#include <iostream>
#include <iterator>

int main(){

    std::vector<double> v{8,8};
    auto i = std::back_inserter(v);
    for(int j=0; j<5; j++, i)
        i=j;

    for(int j : v)
        std::cout<<j<<" ";
    std::cout<<"\n";
}
