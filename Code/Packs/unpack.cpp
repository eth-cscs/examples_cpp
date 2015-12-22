#include <iostream>

template <typename T>
int
convert_to_int(T const& x) {
    return x;
}

void print() {
    std::cout << "End" << std::endl;
}

template <typename F, typename... T>
void
print(F f, T... x) {
    std::cout << f << ", ";
    print(x...);
}

template <typename ... Ts>
void
call(Ts const&...  xs) {
    print(convert_to_int(xs)...);
}

int main() {
    int x=10, y=16;
    double f=4.5;

    call(x,y,f);

}
