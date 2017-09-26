constexpr double f(){return 13.2;}
int main(){
    constexpr double d=13.2;
    static_assert(d==13.2, "");
    static_assert(f()==13.2, "");
}
