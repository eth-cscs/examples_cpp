#include <vector>
#include <iostream>
#include <bitset>

int main(){

    std::vector< bool > v_={true, false, true};
    std::cout<<v_.size()<<"\n";
    constexpr std::bitset<3> b_(0b101);
    std::cout<<sizeof(v_)<<" != "<<sizeof(b_)<<"\n";
    std::cout<<b_[2]<<" = "<<v_[2]<<"\n";
    static_assert(b_[1]==0, "");
}
