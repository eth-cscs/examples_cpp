template<class T, T v>
struct integral_constant {
    typedef T value_type;
    static constexpr value_type value = v;
};



int main() {
    static_assert(integral_constant<int, 7>::value == 7, “Error”)
}
