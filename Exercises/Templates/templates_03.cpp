#ifdef NDEBUG
#undef NDEBUG
#endif

#include <iostream>
#include <cassert>

template <typename T, typename U>
struct X {
    std::string m_name = "X<T,U>";
public:
    std::string const& name() const {return m_name;}
};


template <typename T, typename U>
struct X<T, X<T,U>> {
    std::string m_name = "X<T, X<T,U>>";
public:
    std::string const& name() const {return m_name;}
};

template <typename T>
std::string foo(X<T,T>) {
    return "X<T,T>";
}

template <typename T, typename U>
std::string foo(X<T,U>) {
    return "X<T,U>";
}

int main() {
    std::cout << " > templates_03 <\n";

    X<int, int> x1;
    assert(x1.name() == "????");

    X<int, X<int,float>> x2;
    assert(x2.name() == "????");

    X<int, X<char,X<int,void>>> x3;
    assert(x3.name() == "????");

    assert(foo(x1) == "????");

    assert(foo(x3) == "????");
}
