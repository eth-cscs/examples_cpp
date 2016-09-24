#include<vector>
#include<iostream>
#include<iterator>

struct my_class{
    my_class() = default;
    my_class(my_class const&){std::cout<<"Copy\n";};
    my_class(my_class &&){std::cout<<"Move\n";};
};

int main(){
    std::vector<my_class> v(1);
    auto it = v.begin();
    //auto it = make_move_iterator(v.begin());
    auto moved=my_class(*it);
}
