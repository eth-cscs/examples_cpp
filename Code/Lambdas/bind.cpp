#include <functional>
#include <cassert>
#include "../show.h"
#include <cxxabi.h>
#include <memory>

std::shared_ptr<char> cppDemangle(const char *abiName)
{
    int status;
    char *ret = abi::__cxa_demangle(abiName, 0, 0, &status);

    /* NOTE: must free() the returned char when done with it! */
    std::shared_ptr<char> retval;
    retval.reset( (char *)ret, [](char *mem) { if (mem) free((void*)mem); } );
    return retval;
}

int foo(int const &a, int const& b) { std::cout << "foo: "; return a + b;}

int foo1(int a, int b) { std::cout << "foo1: "; return a + b;}

int bar(int &a, int &b) {return a + b++;}

void run(int (*f)(int, int)) {
    assert(f);
    std::cout << std::hex << (long long)(void*)f << std::dec << "\n";
    SHOW(f(6,4));
}


struct A {
    int v;
    A(int v) : v(v) {}

    static int member(int, int) {return 80;}
    int member2(int, int) {return v;}
};


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

    //y A lambda is automatically converted to function*
    run([](int a, int b) {return a+b;});

    // The following would not work, std::bind returns a type which is not convertible to function*
    //run(std::bind(foo, _1, 4));
    std::cout << "---------------------------------------\n";
    std::function<int(int,int)> my_f = foo1;

    // A std::function cannot be passed as function*
    run(*my_f.target<int(*)(int,int)>());
    std::cout << "---------------------------------------\n";

    // The target member template function is needed
    int(*const* wrongf)(float&) = my_f.target<int(*)(float &)>(); // This is possible but pointer is nullptr
    assert(wrongf == nullptr);

    std::cout << "---------------------------------------\n";
    // So now we can take our binded function and pass it to the C function
    int(*const* to_run)(int,int) = (my_f.target < int(*)(int,int)>());
    assert(to_run);
    run(*to_run);

    std::cout << "---------------------------------------\n";
    std::function<int(int,int)> member1 = A::member;
    to_run = (member1.target < int(*)(int,int)>());
    run(*to_run);
    std::cout << "---------------------------------------\n";
    A a(666);
    std::function<int(A*,int,int)> member2 = &A::member2;
    SHOW(member2(&a, 3,4));
    std::cout << "---------------------------------------\n";
    std::function<int(int,int)> member3 = std::bind(&A::member2, &a, _1, _2);
    SHOW((member3(3,4)));
    std::cout << "---------------------------------------\n";
    std::cout << cppDemangle(member3.target_type().name()) << "\n";
}
