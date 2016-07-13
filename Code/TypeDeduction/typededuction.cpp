#include <iostream>

template <typename T0, typename T1, typename T2>
void
check_these_cr(T0 const& x, T1 const& y, T2 const& z) {
    static_assert(std::is_same<T0, int>::value, "1");
    static_assert(std::is_same<T1, int>::value, "2");
    static_assert(std::is_same<T2, int>::value, "3");

    static_assert(std::is_same<decltype(x), int const&>::value, "1");
    static_assert(std::is_same<decltype(y), int const&>::value, "1");
    static_assert(std::is_same<decltype(z), int const&>::value, "1"); // !!!!

    #if __cplusplus >= 201402L
    decltype(auto) _x = x;
    static_assert(std::is_same<decltype(_x), const int&>::value, "1");
    decltype(auto) _y = y;
    static_assert(std::is_same<decltype(_x), const int&>::value, "1");
    decltype(auto) _z = z;
    static_assert(std::is_same<decltype(_x), const int&>::value, "1");
#endif
}

template <typename T0, typename T1, typename T2>
void
check_these_rvr(T0 && x, T1 && y, T2 && z) {
    static_assert(std::is_same<T0, int&>::value, "1");
    static_assert(std::is_same<T1, int const&>::value, "2");
    static_assert(std::is_same<T2, int>::value, "3");

    static_assert(std::is_same<decltype(x), int&>::value, "1");
    static_assert(std::is_same<decltype(y), int const&>::value, "1");
    static_assert(std::is_same<decltype(z), int&&>::value, "1"); // !!!!

    {
        auto _x = x;
        static_assert(std::is_same<decltype(_x), int>::value, "1");
        auto _y = y;
        static_assert(std::is_same<decltype(_y), int>::value, "1");
        auto _z = z;
        static_assert(std::is_same<decltype(_z), int>::value, "1"); // !!!!
    }

    {
        auto& _x = x;
        static_assert(std::is_same<decltype(_x), int&>::value, "1");
        auto& _y = y;
        static_assert(std::is_same<decltype(_y), int const&>::value, "1");
        auto& _z = z;
        static_assert(std::is_same<decltype(_z), int&>::value, "1"); // !!!!
    }

    {
        auto&& _x = x;
        static_assert(std::is_same<decltype(_x), int&>::value, "1");
        auto&& _y = y;
        static_assert(std::is_same<decltype(_y), int const&>::value, "1");
        auto&& _z = z;
        static_assert(std::is_same<decltype(_z), int&>::value, "1"); // !!!!
    }

#if __cplusplus >= 201402L
    {
        decltype(auto) _x = x;
        static_assert(std::is_same<decltype(_x), decltype(x)>::value, "1");
        decltype(auto) _y = y;
        static_assert(std::is_same<decltype(_y), decltype(y)>::value, "1");
        decltype(auto) _z = std::move(z);
        static_assert(std::is_same<decltype(_z), decltype(z)>::value, "1"); // !!!!
    }
#endif
}



int main() {
    int x = 10;
    int const& y = x;

    check_these_cr(x, y, 10);
    check_these_rvr(x, y, 10);

}
