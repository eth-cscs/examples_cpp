// The following code comes from http://en.cppreference.com/w/cpp/language/value_initialization

#include <string>
#include <vector>
#include <iostream>
#include "../show.h"

struct T1
{
    int mem1;
    std::string mem2;
}; // implicit default constructor

struct T2
{
    int mem1;
    std::string mem2;
    T2(const T2&) { } // user-provided copy constructor
};                    // no default constructor

struct T3
{
    int mem1;
    std::string mem2;
    T3() { } // user-provided default constructor
};

struct T4
{
    int mem1=0;
    std::string mem2="I'm alive";
    T4() { } // user-provided default constructor
};

std::string s{}; // class => default-initialization, the value is ""
// std::string s_(); // Error: function declaration - link time error if used

void test()
{
    int m;                  // scalar => default initialized to indeterminate value
    int n{};                // scalar => zero-initialization, the value is 0
    // int n();             // Error: this is a function declaration
    int x = int{};          // nameless value
    double f = double();    // scalar => zero-initialization, the value is 0.0

    SHOW(m);
    SHOW(n);
    SHOW(x);
    SHOW(f);

    int* a = new int[10](); // array => value-initialization of each element
                            // the value of each element is 0
    int* b = new int[10];   // array => default-initialization of each element
                            // the value of each element is indeterminate

    int* c = new int[10]{5}; // array => BEWARE: initializer_list!!

    T1 t1{};                // class with implicit default constructor =>
    //     t1.mem1 is zero-initialized, the value is 0
    //     t1.mem2 is default-initialized, the value is ""
    T1 t1_b;                //
    //     t1.mem1 is default-initialized to indeterminate
    //     t1.mem2 is default-initialized, the value is ""
//  T2 t2{};                // error: class with no default constructor
    T3 t3{};                // class with user-provided default constructor =>
    //     t3.mem1 is default-initialized to indeterminate value
    //     t3.mem2 is default-initialized, the value is ""
    T4 t4{};                // class with user-provided default constructor =>
    //     t3.mem1 is default-initialized to indeterminate value
    //     t3.mem2 is default-initialized, the value is ""

    std::vector<int> v(3)/* or ()*/;  // value-initialization of each element
                                      // the value of each element is 0

    std::vector<int> w{3};  // initializer_list initialization!!

    SHOW(s.size());
    SHOW(a[1]);
    SHOW(b[1]);
    SHOW(c[1]);
    SHOW(v[2]);
    SHOW(w[2]);
    SHOW(v.size());
    SHOW(w.size());

    SHOW(t1.mem1);
    SHOW(t1_b.mem1);
    SHOW(t1.mem2);
    SHOW(t1_b.mem2);
    SHOW(t3.mem1);
    SHOW(t4.mem1);

    SHOW(t1.mem2);
    SHOW(t3.mem2);
    SHOW(t4.mem2);

    delete[] a;
    delete[] b;
}

int main() {
    test();
}

