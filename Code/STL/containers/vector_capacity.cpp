#include <vector>
#include <iostream>

int main(){
    std::vector< char > v_(2001);
    std::cout<<v_.capacity()<<" "; // 2001
    v_.push_back('b');
    std::cout<<v_.capacity()<<" "; // 4002
    v_.shrink_to_fit();
    std::cout<<v_.capacity()<<"\n"; // 2002
    v_.reserve(2004);v_.push_back('d');
    std::cout<<v_.capacity()<<"\n"; // 2005
}
