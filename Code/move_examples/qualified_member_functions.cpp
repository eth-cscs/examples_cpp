struct A {
    void callme() &{}
    void callme() &&{}
    //void callme() const {}
};

int main() {
    A a;
    a.callme();
    A().callme();
}
