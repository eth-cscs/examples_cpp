

template < typename F, typename S >
struct pair {
    F first;
    S second;

    pair(F f, S s) : first{f}, second{s} {}

    ~pair() {}
};
