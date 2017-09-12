/**@brief Expression summing two arguments*/
namespace expressions{
template <typename T1, typename T2>
struct expr_plus{
    T1 arg1;
    T2 arg2;

    constexpr expr_plus(T1 arg1, T2 arg2) : arg1(arg1), arg2(arg2) {}

    std::string to_string() const {
        return std::string("(") + arg1.to_string() + " + " + arg2.to_string() + std::string(")") ;
    }

    template<typename T>
    constexpr auto operator() (T t_) const{
        return arg1(t_)+arg2(t_);
    }

    //solution exercice 1
    constexpr int sum_ops() const {
        return arg1.sum_ops()+arg2.sum_ops()+1;
    }
    constexpr int mult_ops() const {
        return arg1.mult_ops()+arg2.mult_ops();
    }
    //////////////////////
};

    /** sum expression*/
    template<typename T1, typename T2>
    constexpr expr_plus<T1, T2>
    operator + (T1 arg1, T2 arg2){
        return expr_plus<T1, T2 >(arg1, arg2);}

} //namespace expressions
