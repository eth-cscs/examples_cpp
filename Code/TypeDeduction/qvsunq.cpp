struct A {
    static int n;
};

int A::n;

int main() {
    int A;
    A::n = 42;
    //A b;
}
