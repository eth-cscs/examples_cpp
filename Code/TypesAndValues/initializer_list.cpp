#include <vector>
#include <algorithm>
#include <iostream>

class X {
    std::vector<char> v;
public:
    X(std::initializer_list<char> const& chars)
            : v{chars}
    {
        std::for_each(chars.begin(), chars.end(),
                      [](char c) {std::cout << c;});
        std::cout << std::endl;
    }
};

template <typename T>
void f(T const& chars) {
    std::for_each(chars.begin(), chars.end(),
                  [](char c) {std::cout << c;});
    std::cout << std::endl;
}

int main() {
    X x{'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!'};
    X y = {'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!'};

    //f({'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!'});
    f(std::initializer_list<char>{'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!'});

}
