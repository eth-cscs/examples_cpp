#include <iostream>
#include <algorithm>

template <typename Derived>
class base {
    // Use the two following instead of casting explicitly every time
    Derived& derived() {
        return *static_cast<Derived*>(this);
    }

    Derived const& derived() const {
        return *static_cast<const Derived*>(this);
    }

public:

    template <typename T>
    T process1(T const& v) const {
        ...
    }

    template <typename T>
    T process2(T const& v) {
        ...
    }

    // Stats count how many times process1 and process2 have been called
    void stats() const {
        ...
    }
};

class derived1 : public base<derived1> {
public:
    derived1() : base<derived1>() {}

    std::string process1_impl(std::string const& s) const {
        std::string out;
        for (auto it : s) {
            out += std::toupper(it);
        }

        return out;
    }

    static std::string process2_impl(std::string const& s) {
        std::string out;
        for (auto it : s) {
            out += std::tolower(it);
        }

        return out;
    }
};


int main() {

    derived1 d1;
    std::cout << d1.process1(std::string("Hello World!")) << std::endl;
    std::cout << d1.process2(std::string("Hello World!")) << std::endl;
    std::cout << d1.process2(std::string("Hello ... Well, you get the point")) << std::endl;

    // To finish, print the number of times process1 and process2 have been called
    d1.stats();

}
