#include <vector>
#include <iostream>
#include <iterator>

int main(){
    std::vector<int> v{0,1,2,3};
    for(auto i=v.rbegin(); i!=v.rend(); ++i)
        std::cout<<*i<<" ";
    std::cout<<"\n";
}
