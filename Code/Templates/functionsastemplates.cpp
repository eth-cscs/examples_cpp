#include "../show.h"

template <typename ...T>
using void_ = void;

void foo(int &x) { std::cout << "Function foo& " << (x++) << "\n"; }
void foo_(int x) { std::cout << "Function foo&& " << (x++) << "\n"; }

struct bar {
    bar() {std::cout << "bar constructor\n";}
    void operator()(int &x) {std::cout << "Execute bar " << (x++) << "\n";}
    void operator()(int&& x) {std::cout << "Execute bar " << (x++) << "\n";}
};




template <typename Ret, typename ...Args>
void deduce_run(Ret(*F)(Args...), Args&&... args) {
    std::cout << "deduce_run void(*)()\n";
    F(std::forward<Args>(args)...);
}


template <typename F, typename ...Ts>
void deduce_run(F, Ts&& ...vs) {
     std::cout << "deduce_run functor\n";
     F{}(std::forward<Ts>(vs)...);
}

int main() {
    deduce_run(foo_, 4);
    deduce_run(bar(), 5);

    int i = 4;
    SHOW(i);
    deduce_run(foo, i);
    SHOW(i);
    deduce_run(bar(), i);
    SHOW(i);

}
