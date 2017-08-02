#include <iostream>

template <typename T>
T add1(T x) { return x + 1; }

std::string add1(std::string x) { return x + "1"; }


int execute(int(*fp)(int), int a) {
    return fp(a);
}

template <typename T>
T execute(T(*fp)(T), T a) {
    return fp(a);
}


int main() {

    int x = 64;

    std::cout << "As int    " << add1(x) << "\n"; // Should print 65

    std::cout << "As char   " << add1<char>(x) << "\n"; // Should print 'A'

    std::cout << "As string " << add1(std::string("64 + ")) << "\n";

    int (*fp)(int) = add1;

    std::cout << execute(fp, 41) << "\n";

    float (*flp)(float) = add1;

    std::cout << execute(flp, 40.9999f) << "\n";

}
