#include<vector>
#include<iostream>

main(){
    std::vector<int> q_({0,1,2,3,4,5,6,7});
    std::cout<<q_[2]<<"==2\n";
    std::cout<<q_.size()<<"\n";
    std::cout<<q_.capacity()<<"\n";
    q_.push_back(0);
    std::cout<<q_.size()<<"\n";
    std::cout<<q_.capacity()<<"\n";
    //std::vector<int,  my_stack_allocator<int> > qq_(101); //throws bad_alloc
}
