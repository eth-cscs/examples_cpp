template <typename T, typename U>
void foo(T,U) {};

namespace N0 {
    struct X{};
    template <typename T>
    void foo(X,T) {}
}
namespace N1 {
    struct Y {};
    template <typename T>
    void foo(T,Y) {}
}

int main() {
    // The following is ambiguous for all the candidates
    //foo(N0::X{}, N1::Y{});

    ::foo(N0::X{}, N1::Y{});
    N0::foo(N0::X{}, N1::Y{});
    N1::foo(N0::X{}, N1::Y{});
}
