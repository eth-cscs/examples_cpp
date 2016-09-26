struct A {
    static int n;
};

int A::n = 10;

int main() {
    int A; A = 10;
    A::n = 42;
    //   A b;
}
