#ifdef NDEBUG
#undef NDEBUG
#endif

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

int main() {

    std::size_t s;
    std::cout << "This program will take a sequence of integer values and \nprint the prefix sum of those values starting from a given value\n:";

    std::cout << "Number of elements\n:";
    std::cin >> s;

    std::vector<int> data(s);

    std::for_each(data.begin(), data.end(),
                  [](int& x) { std::cout << ":"; std::cin >> x;});

    std::cout << "Enter the starting value\n:";
    int m{};
    std::cin >> m;
    int old_m = m;

    std::for_each(data.begin(), data.end(),
                  [m](int &x) mutable { x += m; m=x; });
    std::cout << "\nhelloooo" << m << "\n";

    assert(m==old_m);

    std::for_each(data.begin(), data.end(),
                  [](int x) { std::cout << x << " ";});
    std::cout << "\n";

}
