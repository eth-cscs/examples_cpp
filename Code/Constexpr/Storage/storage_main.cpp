#include <utility>
#include <iostream>

template <int Size>
struct storage_info{

    template <typename ... Dims>
    constexpr storage_info(Dims ... dims_) : m_dims{dims_ ...}{}

    static constexpr int size(){return Size;}

    template<int Coord>
    constexpr int dim() const {return m_dims[Coord];}

private:
    int m_dims[Size];
};

int main(){
    constexpr storage_info<5> c_{2,3,4,5,6};
    static_assert(c_.index(1,0,0,0,0)==1, "error");
    static_assert(c_.index(0,1,0,0,0)==2, "error");
    static_assert(c_.index(0,0,1,0,0)==3*2, "error");
    static_assert(c_.index(0,0,0,1,0)==4*3*2, "error");
    static_assert(c_.index(0,0,0,0,1)==5*4*3*2, "error");
}
