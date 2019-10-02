#include <iostream>

template <typename T>
class A {
    T x;
public:
    A(T x) : x{x} {}
};

template <typename T>
class A2 {
    T x;
public:
    template <typename U>
    A2(T x, U, int) : x{x} {}
};

template <typename F>
struct B {
    F f;
    B(F&& f) : f{std::move(f)} {}

    template <typename ...Args>
        void call(Args&&... args) {
        f(std::forward<Args>(args)...);
    }
};


template <typename T>
A<T> make_A(T a) {
    return A<T>{a};
}

template <typename T>
A2<T> make_copy_A2(A2<T> a) {
    return A2<T>{a};
}

template <typename T, typename U>
A2<T> make_A2(T a, U x, int y) {
    return A2<T>{a, x, y};
}

int main() {
    {
        A<int> x(3);
        A y(3);

        auto z = make_A(3);
    }
    {
        A2 x(3, 4.5, 8);

        auto z = make_A2(3, 4.5, 8);

        A2 y{x};

        auto y2 = make_copy_A2(y);
    }
    auto f = [](int i, int j) { std::cout << i+j << "\n"; };
    B<decltype(f)> a{std::move(f)};

    B b{[](int i, int j) { std::cout << i+j << "\n"; }};

    B c{[](int i, int j) { std::cout << i-j << "\n"; }};

    a.call(3,4);
    b.call(3,4);
    c.call(3,4);
}
