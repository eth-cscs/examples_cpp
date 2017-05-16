#include <utility>

struct T {
    T() = default;
    T(T const&) = default;
    T(T&&, int =10) {}
};

void f(T x) {}

int main() {
    T y;
    f(y);
    f(T{});
    f(std::move(y));
}
