#include <vector>
#include <algorithm>
#include "../show.h"

template <typename IT, typename F>
void for_each(IT begin, IT end, F f) {
    std::cout << "My for each\n";
    std::for_each(begin, end, f);
};

int main() {
    std::vector<int> v(10);
    // The following call is ambiguous!!
    //for_each(v.begin(), v.end(), [](int &i){ ++i; std::cout << i << " ";});
    // Either do for a std:: implementation:
    std::for_each(v.begin(), v.end(), [](int &i) {
        ++i;
        std::cout << i << " ";
    });
    std::cout << "\n";
    // Or do :: for the global namespace implementation:
    ::for_each(v.begin(), v.end(), [](int &i) {
        ++i;
        std::cout << i << " ";
    });
    std::cout << "\n";
}
