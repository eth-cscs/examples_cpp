#include <type_traits>
#include "../show.h"
#include <iomanip>
#include <algorithm>
#include <vector>

int ten(int) {return 10;}
int& foo(int& x) {return x;}

template <typename F>
decltype(auto) inc(F f, int& v) {
    decltype(auto) x = f(v);
    x++;
    return x;
}


struct elem_t {
    int _value;
    bool _mark;
    int& value() {return _value;}
    bool& mark() {return _mark;}
};


struct proxy {
    std::vector<elem_t>& v;
    unsigned index = 0;

    proxy(std::vector<elem_t>& v, unsigned i)
        : v(v), index(i)
    {}

    elem_t* addr() { return &v[index];}
    int& value() { return v[index].value(); }
    bool& mark() { return v[index].mark(); }
};

struct my_array {
    std::vector<elem_t> x;

    my_array(std::initializer_list<elem_t> const& l)
        : x(l) {}

    proxy operator[](unsigned i) {
        return proxy(x, i);
    }
};

template <typename Array, typename Pred>
void mark_if(Array & a, unsigned index, Pred const& pred) {
    elem_t& ref = a[index];
    if (pred(ref.value())) {
        ref.mark() = true;
    }
}

int main() {
    {
        decltype(auto) y = 10;
        static_assert(std::is_same<decltype(y), int>::value, "");
    }
    {
        int x = 10;
        int& z = x;
        decltype(auto) y = x;
        static_assert(std::is_same<decltype(y), int>::value, "");
        decltype(auto) w = z;
        static_assert(std::is_same<decltype(z), int&>::value, "");
    }

    {
        int x = 10;
        SHOW(x);
        SHOW(inc(ten, x));
        SHOW(x);
        SHOW(inc(foo, x));
        SHOW(x);
    }

    {
        elem_t array[3] = { {1,false}, {2,false}, {3,false} };
        std::for_each(&array[0], &array[3],
                      [](elem_t x) {
                          std::cout << "{"
                                    << x.value() << ", "
                                    << std::boolalpha << x.mark()
                                    << "}\n";
                      });
        mark_if(array, 1, [](int x) {return x<10;});
        std::for_each(&array[0], &array[3],
                      [](elem_t x) {
                          std::cout << "{"
                                    << x.value() << ", "
                                    << std::boolalpha << x.mark()
                                    << "}\n";
                      });
    }

    {
        my_array array = { {1,false}, {2,false}, {3,false} };
        std::for_each(array[0].addr(), array[3].addr(),
                      [](elem_t x) {
                          std::cout << "{"
                                    << x.value() << ", "
                                    << std::boolalpha << x.mark()
                                    << "}\n";
                      });
        mark_if(array, 1, [](int x) {return x<10;});
        std::for_each(array[0].addr(), array[3].addr(),
                      [](elem_t x) {
                          std::cout << "{"
                                    << x.value() << ", "
                                    << std::boolalpha << x.mark()
                                    << "}\n";
                      });
    }
}
