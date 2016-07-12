// Template arguments are evaluated left to right. The following line is wrong
//template <typename T, int X = U::value, typename U = typename T::type>
template <typename T, typename U = typename T::type, int X = U::value>
struct Order {};

struct B {
    using type = B;
    static const int value = 100;
};

int main() {
    Order<B> x;
}
