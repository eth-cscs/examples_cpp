// A metafunction that finds the type in a sequence of types
// that has the biggest sizeof value, plus it should return the size

#include "../../Code/show.h"

int main() {
    SHOW((find_max_size<char, int, double, float>::value));
    static_assert((std::is_same<double, find_max_size<char, int, double, float>::type>::value), "not ok");
}
