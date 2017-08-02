#ifdef NDEBUG
#undef NDEBUG
#endif

#include <iostream>
#include <cassert>

template <typename T, typename U>
class my_class {
    std::string m_name = "my_class<T,U>";
public:
    std::string const& name() const {return m_name;}
};

template <????>
class my_class<????> {
    std::string m_name = "my_class<T,int>";
public:
    std::string const& name() const {return m_name;}
};

template <????>
class my_class<????> {
    std::string m_name = "my_class<int,int>";
public:
    std::string const& name() const {return m_name;}
};


int main() {

    std::cout << " > templates_02 <\n";

    my_class<int,int> a;

    assert(a.name() == "my_class<int,int>");

    my_class<int,char> b;

    assert(b.name() == "my_class<T,U>");

    my_class<char,int> c;

    assert(c.name() == "my_class<T,int>");

}
