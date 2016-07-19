#include <iosfwd>
#include <vector>
#include "../show.h"

struct complex {
    double re, im;

    complex & operator+=(complex d) {
        im += d.im;
        re += d.re;
        return *this;
    }
};

std::ostream& operator<<(std::ostream& s, complex c) {
    return s << c.re << " + i" << c.im;
}


int main() {
    auto make_complex = [](double a, double b) -> complex {return {a,b};};
    SHOW((make_complex(1.4, 3.2)));

    auto copy_complex = [](complex c) -> complex {return c;};
    complex copy = copy_complex(complex{4.,2.});
    SHOW(copy);

#if __cplusplus>=201402L
    auto sum_inplace = [](complex &c, complex d) -> auto& {c += d; return c;};
#else
    auto sum_inplace = [](complex &c, complex d) -> complex& {c += d; return c;};
#endif
    complex x{0.,0.};
    auto& xr = sum_inplace(x, complex{4.,2.});
    SHOW(xr);
    x.im = 42;
    SHOW(xr);
}

