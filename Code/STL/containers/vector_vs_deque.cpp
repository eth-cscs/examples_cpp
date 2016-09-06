#include <vector>

int main(){

    std::vector< int > l_(1e8);

    for(auto i=1; i < 1e8; i++){
        l_.push_back(8);
        //l_.insert(l_.begin(), 8);
    }
}
