#ifdef NDEBUG
#undef NDEBUG
#endif

#include <iostream>
#include <cassert>

int main() {

    {
        auto sum = []( ???? ) { return i+j;};

        assert(sum(3,5) == 8);
    }

    {
        int i;

        auto initialize = [????](int j) {i=j;};

        initialize(42);
        assert(i==42);
    }

    std::string prefix("hello");

    {
        auto concat = [????](std::string s) ???? {return prefix + " " + s;};

        std::cout << concat("world") << " \n";
        assert( ("hello world") == concat("world") );
    }

    {
        auto concat2 = [????](std::string s) ???? {prefix[0] = std::toupper(prefix[0]); return prefix + " " + s;};

        std::cout << concat2("world") << " \n";
        assert( ("Hello world") == concat2("world") );
    }

    {
        auto concat3 = [????](????) ???? {prefix[0] = std::toupper(prefix[0]); return prefix + " " + s + " " + std::to_string(index);};

        assert( ("Hello world 42") == concat3("world", 42) );

        std::cout << concat3("world", 42) << " \n";
    }
}
