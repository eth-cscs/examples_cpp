#include <iostream>

struct stream_proxy {

    std::ostream* sptr = nullptr;

    stream_proxy(std::ostream & s)
        : sptr(&s)
    {}

    stream_proxy& operator=(std::ostream& s) {
        sptr = &s;
        return *this;
    }

    template <typename T>
    stream_proxy& operator<<(T const& x) {
        *sptr << "*" << x;
        return *this;
    }
};


int main () {
    stream_proxy s(std::cout);

    s << "Hello " << "world" << "\n";

    s = std::cerr;

    s << "Hello " << "world on std::err" << "\n";

    s = std::cout;

    s << "Hello " << "world" << "\n";

    s = std::cerr;

    s << "Hello " << "world on std::err" << "\n";
}
