struct test{
    constexpr test(int arg_) : m_val{arg_}{}
    constexpr int get() const {return m_val;}
    int m_val;
};

int main(){
    constexpr test t1_(5);
    test t2_(10);
    constexpr bool check_t1_ = (noexcept(t1_.get()));
    constexpr bool check_t2_ = (noexcept(t2_.get()));

#ifndef __clang__
#if __GNUG__ < 6
    static_assert(check_t1_==true, "error");
    static_assert(check_t2_==false, "error");
#endif
#endif
}
