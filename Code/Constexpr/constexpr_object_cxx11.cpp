#include <tuple>
#include <iostream>

struct my_const_struct{
    int m_i;

    constexpr my_const_struct(int x) : m_i(x) { }
    constexpr int get() const {return m_i;}
};

int main(){
    constexpr my_const_struct my_struct(10);
    std::cout<<my_struct.get()<<"\n";
    static_assert(my_struct.get()==10, "error");
}
