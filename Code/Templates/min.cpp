#include "../show.h"

template <typename T>
T const& min(T const& a, T const& b) {
    return (a<b)?a:b;
}


//////
 template <typename T>
T const* min(T const* const a, T const* const b) {
    std::cout << " *ptr spcialization* ";
    return (*a<*b)?a:b;
}

char const* min(const char * const a, const char * const b) {
    std::cout << " *char specialization* ";
    return (std::string(a) < std::string(b)?a:b);
}

int main() {
    SHOW((min(3,4)));

//   SHOW((min("Allucination", "Dream")))
    SHOW((min("Alluc", "Dream")))

//    char const* const c0 = "423";
//    char const* const c1 = "234";
    char const c0[4] = "423";
    char const c1[4] = "234";
    SHOW((min(c0, c1))); // ??? Exercise 1: find a way of comparing pointers, find a way of comparing char const* // the commented code above

//    SHOW((min<std::string>(c0,c1)));


}
