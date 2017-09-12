constexpr auto f_(){return 5;}

int main(){
    static_assert(f_()==5, "error"); // this works

    constexpr auto f = []()->int{ return 5;};
    static_assert(f()==5, "error"); // this does not work
}
