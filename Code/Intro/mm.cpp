#include <iostream>
#include <sys/time.h>

static const int n = 2324;
static const int m = 1356;
static const int l = 746;

double c[n][m];
double a[n][l];
double b[l][m];

void init() {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            c[i][j] = 0.;

    for (int i = 0; i < n; ++i)
        for (int k = 0; k < l; ++k)
            a[i][k] = i+k;

    for (int k = 0; k < l; ++k)
        for (int j = 0; j < m; ++j)
            c[k][j] = k+j;
}

void mm1() {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            for (int k = 0; k < l; ++k)
                c[i][j] += a[i][k] * b[k][j];
}

void mm2() {
    for (int i = 0; i < n; ++i)
        for (int k = 0; k < l; ++k)
            for (int j = 0; j < m; ++j)
                c[i][j] += a[i][k] * b[k][j];
}

double tic() {
    static timeval t;
    gettimeofday(&t, nullptr);
    return (double)t.tv_sec * 1.e6 + (double)t.tv_usec;
}

int main() {
    double start;

    start = tic();
    mm1();
    std::cout << tic()-start << "\n";

    start = tic();
    mm2();
    std::cout << tic()-start << "\n";

    start = tic();
    mm1();
    std::cout << tic()-start << "\n";

    start = tic();
    mm2();
    std::cout << tic()-start << "\n";
}
