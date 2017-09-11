#ifdef NDEBUG
#undef NDEBUG
#endif

#include <iostream>
#include <cassert>

int main() {

    auto sum = [](int i, int j) { return i+j;};

    assert(sum(3,5) == 8);

    int i;

    auto initialize = [&i](int j) {i=j;};

    initialize(42);
    assert(i==42);

    std::string prefix("hello");
    auto concat = [prefix](std::string s) {return prefix + " " + s;};

    std::cout << concat("world") << " OH!\n";
    assert( ("hello world") == concat("world") );

    auto concat2 = [prefix](std::string s) mutable {prefix[0] = std::toupper(prefix[0]); return prefix + " " + s;};

    std::cout << concat2("world") << " OH!\n";
    assert( ("Hello world") == concat2("world") );

    auto concat3 = [prefix](std::string s, int index) mutable {prefix[0] = std::toupper(prefix[0]); return prefix + " " + s + " " + std::to_string(index);};

    assert( ("Hello world 42") == concat3("world", 42) );

    std::cout << concat3("world", 42) << " OH!\n";
}
