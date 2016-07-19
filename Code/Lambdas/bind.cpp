#include <functional>
#include <cassert>
#include "../show.h"

int foo(int const &a, int const& b) { std::cout << "foo: "; return a + b;}

int foo1(int a, int b) { std::cout << "foo1: "; return a + b;}

int bar(int &a, int &b) {return a + b++;}

void run(int (*f)(int, int)) {
    assert(f);
    std::cout << std::hex << (long long)(void*)f << std::dec << "\n";
    SHOW(f(6,4));
}

int main() {
    using namespace std::placeholders;

    // Take a two argument function and bind an argument to be 4
    SHOW((std::bind(foo, _1, 4)(6)));

    int x = 4;
    // If the function takes a const& argument, then the bind needs to say it
    SHOW(std::bind(foo, _1, std::cref(x))(6));

    // If the argumet is actually a reference...
    int y = 6;
    SHOW(std::bind(bar, _1, std::ref(x))(y));
    SHOW(x);

    // A lambda is automatically converted to function*
    run([](int a, int b) {return a+b;});

    // The following would not work, std::bind returns a type which is not convertible to function*
    // run(std::bind(foo, _1, 4));

    std::function<int(int,int)> my_f = foo1;

    // A std::function cannot be passed as function*
    //run(binded1);

    // The target member template function is needed
    auto wrongf = my_f.target<int(float &)>(); // This is possible but pointer is nullptr
    assert(*wrongf == nullptr);

    // So now we can take our binded function and pass it to the C function
    auto to_run = *(my_f.target < int(*)(int,int)>());
    assert(to_run);
    run(to_run);
}