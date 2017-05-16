#include<array>
int main(){
    constexpr std::array<int, 5> arr_{0,1,2,3,4};
    static_assert(arr_[2] ==  2, "error");
    static_assert(std::get<2>(arr_) == 2, "error");
    static_assert(arr_.size() == 5, "error");
    static_assert(arr_.back() == 4, "error");
    static_assert(arr_.front() == 0, "error");
    std::array<int, 2> arr1_{1,0}, arr2_{0,1};
    arr2_.swap(arr1_);
    auto out_of_bound=arr1_[5];
}
