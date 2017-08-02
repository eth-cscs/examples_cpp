#include "../show.h"

template <typename T, typename Return=char>
Return foo(T x) {
    return static_cast<Return>(x);
}

template <typename T=double, int size=10>
struct my_container {
    my_container() {std::cout << "Primary " << size << "\n";}
};

template <typename T>
struct my_container<T, 10> {
    my_container() {std::cout << "THIS IS JUST 10\n";}
};

template <typename T>
struct my_container<T, 15> {
    my_container() {std::cout << "THIS IS JUST 15\n";}
};

int main() {

    // For functions:
    SHOW(foo(65));
    SHOW((foo<int, int>(65)))

    // For classes
    my_container<> x; // a my_container of doubles
                      // <>  are needed since my_container is a template!
    my_container<int> y;
    my_container<char, 10> z;
    my_container<float,30> u;
    my_container<int, 15> v;

}
