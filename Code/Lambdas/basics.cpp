#include "../show.h"

int main() {
    std::cout << "\n\nBasic Lambda with 2 arguments\n";
    {
        auto f = [](int a, int b) { return a + b; };
        SHOW((f(3, 4)));
    }
    std::cout << "\n\nLambda that capture a variable by value\n";
    {
        bool sum = true;
        auto f = [sum](int a, int b) { SHOW_BOOL(sum); return sum?(a + b):(a-b); };
        SHOW((f(3, 4)));
    }
#if __cplusplus==201402L
    std::cout << "\n\nLambda that capture a variable by value and renames it\n";
    {
        bool sum = true;
        auto f = [flag=sum](int a, int b) { SHOW_BOOL(flag); return flag?(a + b):(a-b); };
        SHOW((f(3, 4)));
    }
#endif
    std::cout << "\n\nLambda that capture a variable by value and one by reference\n";
    {
        bool sum = true;
        int x = 42;
        auto f = [sum, &x](int a, int b) { x = !sum?(a + b):(a-b); return sum?(a + b):(a-b); };
        SHOW((f(3, 4)));
        SHOW(x);
    }
    std::cout << "\n\nMutable Lambda: the by-value capture can be varied with the body. No side-effects\n";
    {
        bool sum = true;
        int x = 42;
        auto f = [sum, &x](int a, int b) mutable { sum = ((x>0) == !sum); SHOW_BOOL(sum); return sum?(a + b):(a-b); };

        SHOW((f(3, 4)));
        SHOW(x);
        SHOW_BOOL(sum); // sum is not changed, the "member" of the lambda is, since it is marked mutable
    }
    std::cout << "\n\nLambda that captures everything by reference\n";
    {
        bool sum = true;
        int x = 42;
        auto f = [&](int a, int b) /*mutable*/ { sum = ((x>0) == !sum); x=7; SHOW_BOOL(sum); return sum?(a + b):(a-b); };

        SHOW((f(3, 4)));
        SHOW(x);
        SHOW_BOOL(sum); // sum is not changed, the "member" of the lambda is, since it is marked mutable
    }
    std::cout << "\n\nLambda that captures everything by value\n";
    {
        bool sum = true;
        int x = 42;
        auto f = [=](int a, int b) mutable { sum = ((x>0) == !sum); x=7; SHOW_BOOL(sum); return sum?(a + b):(a-b); };

        SHOW((f(3, 4)));
        SHOW(x);
        SHOW_BOOL(sum); // sum is not changed, the "member" of the lambda is, since it is marked mutable
    }
    std::cout << "\n\nLambda that captures everything by value, but x by reference\n";
    {
        bool sum = true;
        int x = 42;
        auto f = [=, &x](int a, int b) mutable { sum = ((x>0) == !sum); x=7; SHOW_BOOL(sum); return sum?(a + b):(a-b); };

        SHOW((f(3, 4)));
        SHOW(x);
        SHOW_BOOL(sum); // sum is not changed, the "member" of the lambda is, since it is marked mutable
    }
}
