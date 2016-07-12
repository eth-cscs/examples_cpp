#include <string>
#include "../show.h"

double f[35]; // zero-initialized to three 0.0's
int* p;   // zero-initialized to null pointer value
std::string s; // zero-initialized to indeterminate value
// then default-initialized to ""

void test()
{
    double f_[15]; // non static, so not initialized
    static int n; // zero-initialized to 0 (static)
    int m; // default initialize to indeterminate

    char hello[17] = "hello"; // values after "hello" are zero initialized

    SHOW(f[0]);
    SHOW(f[1]);
    SHOW(f[2]);

    SHOW(f_[0]);
    SHOW(f_[1]);
    SHOW(f_[2]);

    SHOW(n);
    SHOW(m);

    SHOW(p);

    SHOW(hello);

    for (int i; i<17; ++i) {
        std::cout << static_cast<int>(hello[i]) << " ";
    }
    std::cout << "\n";

    // then copy-initialized to argc
    delete [] p; // safe to delete a null pointer
}

int main() {
    test();
}
