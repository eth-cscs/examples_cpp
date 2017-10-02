#include <tuple>
#include <iostream>

#if __GNUG__  && __GNUC__ < 5
#pragma message("This example require GCC > 5.4, sorry\n")
int main() {}
#else
struct my_const_struct{
    template<typename T>
    constexpr my_const_struct(T t_) : m_i{} {
        bool cond=std::get<2>(t_)<std::get<1>(t_);
        if(cond)
            m_i = std::get<2>(t_);
        else
            m_i = std::get<1>(t_);
    }
    constexpr int get() const {return m_i;}
    int m_i;
    // std::string m_s; //This does not have a constexpr constructor
};

int main(){
    constexpr auto t_=std::make_tuple(1,2,3,4);
    constexpr my_const_struct my_struct(t_);
    std::cout<<my_struct.get()<<"\n";
    static_assert(my_struct.get()==2, "error");
}
#endif
