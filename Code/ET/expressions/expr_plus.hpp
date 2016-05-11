    /**@brief Expression summing two arguments*/
template <typename ArgType1, typename ArgType2>
struct expr_plus{
    std::string to_string() const {
        return std::string("(") + ArgType1().to_string() + " + " + ArgType2().to_string() + std::string(")") ;
        }

    template<typename T>
    constexpr auto operator() (T t_) const{
        return ArgType1()(t_)+ArgType2()(t_);
    }
};

namespace expressions{
    /** sum expression*/
    template<typename ArgType1, typename ArgType2>
    constexpr expr_plus<ArgType1, ArgType2>
    operator + (ArgType1 arg1, ArgType2 arg2){
        return expr_plus<ArgType1, ArgType2 >();}

} //namespace expressions
