    /**@brief Expression summing two arguments*/
namespace expressions{
template <typename T1, typename T2>
struct expr_plus{
    std::string to_string() const {
        return std::string("(") + T1().to_string() + " + " + T2().to_string() + std::string(")") ;
        }

    template<typename T>
    constexpr auto operator() (T t_) const{
        return T1()(t_)+T2()(t_);
    }

    //solution exercice 1
    constexpr int sum_ops() const {
        return T1().sum_ops()+T2().sum_ops()+1;
    }
    constexpr int mult_ops() const {
        return T1().mult_ops()+T2().mult_ops();
    }
    //////////////////////
};

    /** sum expression*/
    template<typename T1, typename T2>
    constexpr expr_plus<T1, T2>
    operator + (T1 arg1, T2 arg2){
        return expr_plus<T1, T2 >();}

} //namespace expressions
