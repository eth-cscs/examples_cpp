#include <vector>
#include <iostream>
#include <iterator>

struct my_class{
    my_class(my_class const&){std::cout<<"Copy\n";};
    my_class(int, double){std::cout<<"Construct\n";};
    // my_class(my_class &&){std::cout<<"Move\n";};
    // void operator = (my_class &&){std::cout<<"Move Assignment\n";};
};

int main(){

    std::vector<my_class> m;
    m.reserve(2);
    m.push_back( my_class(1,2.) );
    m.push_back( my_class(1,2.) );
    //m.emplace_back( 1,2. );
    //m.emplace_back( 1,2. );
    //m.emplace(m.begin(), 1, 2. );
}
