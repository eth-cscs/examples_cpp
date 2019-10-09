#include <cstddef>
#include "../show.h"

struct A {};
struct alignas(double) B {};

template <typename ...Ts>
struct alignas(Ts...) C{};

// struct alignas(char, double) C1{}; // Only packs allowed in alignas!

struct X {
    char a;
    int b;
    char c;
};

struct Y {
    char a;
    alignas(double) int b;
    char c;
};

struct Z {
    char a, b, a1, b1, c, a2, b2, a12, b12;
    int d;
};

template <typename T>
bool check_align(T const* const p, unsigned int alignment) {
    return ((reinterpret_cast<uintptr_t>(static_cast<void const* const>(p))&(alignment-1)) == 0);
};

int main() {
    SHOW(alignof(char));
    SHOW(alignof(int16_t));
    SHOW(alignof(int));
    SHOW(alignof(float))
    SHOW(alignof(double));
    SHOW(alignof(bool));
    SHOW(alignof(A));
    SHOW(alignof(B));
    SHOW(alignof(C<char, double>));

    char a[8];
    alignas(double) char b[8]; // Why?
    float *fp = new(b) float{3.14};
    SHOW(*fp);
    SHOW_BOOL((static_cast<void*>(fp)==static_cast<void*>(b)));

    SHOW(alignof(std::max_align_t));

    alignas(128) char cache_line[128];
    alignas(128) char* p;
    SHOW_BOOL(check_align(cache_line, 128));
    SHOW_BOOL(check_align(&p, 128));
    char p1 = '0';
    p = &p1;
    SHOW_BOOL(check_align(&p, 128));
    SHOW_BOOL(check_align(p, 128));
    SHOW_BOOL(check_align(&p1, 128));

    std::cout << "--------------------------------\n";
    SHOW(sizeof(X));
    SHOW((sizeof(char) + sizeof(int) + sizeof(char)))
    SHOW(sizeof(Y));
    SHOW(sizeof(Z));
    std::cout << "--------------------------------\n";

    int *ip = new int{45};
    SHOW_BOOL(check_align(ip, 128));
    SHOW_BOOL(check_align(ip, 64));
    SHOW_BOOL(check_align(ip, 32));
    SHOW_BOOL(check_align(ip, sizeof(int)));

}
