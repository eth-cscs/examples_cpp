template <typename T, typename U = typename T::type, int X = U::value>
struct Order {};

struct B {
    using type = B;
    static const int value = 100;
};

int main() {
    Order<B> x;
}
