#include "../show.h"
#include <type_traits>

class POD {
    //private: // also good
public:
    int a; /* = 12; // non pod: this is a member initializer */
    int b;
    char c;
};

class DPOD : public POD {
public:
    int d;
};

class non_POD0 {
    int a;
    float b;
public: // Not the same access control
    char c;
};

class non_POD1 {
public:
    int a;
    float b;
    char c;
    non_POD1(int& a, float b, char c) // user defined constructor
            : a(a), b(b), c(c)
    {}
};

class non_POD2 {
public:
    int &a; // reference
    float b;
    char c;
    non_POD2(int& a, float b, char c)
            : a(a), b(b), c(c)
    {}
};

class non_POD3 {
public:
    int a;
    float b;
    char c;
    non_POD3(POD const& ) = delete; // copy constructor even though deleted
};

int main () {
    SHOW_BOOL(std::is_pod<POD>::value)
    SHOW_BOOL(std::is_pod<DPOD>::value)
    SHOW_BOOL(std::is_pod<non_POD0>::value)
    SHOW_BOOL(std::is_pod<non_POD1>::value)
    SHOW_BOOL(std::is_pod<non_POD2>::value)
    SHOW_BOOL(std::is_pod<non_POD3>::value)
}
