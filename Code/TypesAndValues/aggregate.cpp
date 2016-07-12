#include "../show.h"

struct short_array_3 {
    int data3[5];
};

struct short_array_5 {
    int data5[5];

    constexpr int operator[](int i) {
        return data5[i];
    }
};

struct two_arrays {
    short_array_3 _3;
    short_array_5 _5;
    int x;
};

int main() {
    short_array_3 x{1,2,3};
    short_array_3 y = {3,2,1};

    SHOW(x.data3[0])
    SHOW(x.data3[1])
    SHOW(x.data3[2])
    SHOW(y.data3[0])
    SHOW(y.data3[1])
    SHOW(y.data3[2])

    static_assert(short_array_3{1,2,3}.data3[1] == 2, "ok");
    static_assert(short_array_5{1,2,3,4,5}[1] == 2, "ok");

    two_arrays two = {{3,2,1},{5,4,3,2,1}, 324};

    static_assert(two_arrays{{3,2,1},{5,4,3,2,1}, 324}.x == 324, "");
    static_assert(two_arrays{{3,2,1},{5,4,3,2,1}, 324}._5[1] == 4, "");
    static_assert(two_arrays{{3,2,1},{5,4,3,2,1}, 324}._3.data3[0] == 3, "");

    short_array_5 z[2] = {{6,6,6,6,6},{3,3,3,4,4}};
    SHOW(z[1][3]);
    SHOW(z[0][2]);
}