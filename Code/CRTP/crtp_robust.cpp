#include <iostream>
#include <algorithm>

template <typename Derived>
class base {

    int count_process1;
    int count_process2;

private:
    Derived& derived() {
        return *static_cast<Derived*>(this);
    }

public:

    base() : count_process1(0), count_process2(0) {}

    template <typename T>
    T process1(T const& v) {
        ++count_process1;
        derived().process1_impl(v);
    }

    template <typename T>
    T process2(T const& v) {
        ++count_process2;
        Derived::process2_impl(v);
    }

    void stats() const {
        std::cout << "Statistics for base<Derived>\n"
                  << "process1 called " << count_process1 << " times\n"
                  << "process2 called " << count_process2 << " times\n"
                  << std::endl;
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


// class derived2 : base<derived2> {
// };


int main() {

    derived1 d1;
    std::cout << d1.process1(std::string("Hello World!")) << std::endl;
    std::cout << d1.process2(std::string("Hello World!")) << std::endl;

    d1.stats();

}
