#include <vector>

int main(){

    std::vector< int > l_(1e5);

    for(auto i=0; i < 1e5; i++){
        l_.insert(l_.begin()+i, 8);
    }
}
