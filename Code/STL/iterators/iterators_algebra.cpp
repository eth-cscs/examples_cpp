#include<iterator>
#include<vector>
#include<cassert>

int main(){
    std::vector<int> m{0,1,2,3};
    auto it=std::begin(m);
    auto it2=std::next(it);
    assert(*it == 0);
    assert(*it2 == 1);
    assert(std::distance(it, it2)==1);
    assert(*std::prev(it2) == 0);
    assert(*std::prev(std::end(m)) == 3);
}
