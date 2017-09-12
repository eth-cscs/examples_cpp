namespace expressions{

    template <typename T1, typename T2>
    struct expr_times{
        T1 arg1;
        T2 arg2;

        constexpr expr_times(T1 arg1, T2 arg2) : arg1(arg1), arg2(arg2) {}

        template<typename T>
        constexpr auto  operator() (T t_) const{
            return arg1(t_) * arg2(t_);
        }

        std::string to_string() const {
            return std::string("(") + arg1.to_string() + " * " + arg2.to_string() + std::string(")") ;
        }

        //solution exercice 1
        constexpr int sum_ops() const {
            return arg1.sum_ops() + arg2.sum_ops();
        }
        constexpr int mult_ops() const {
            return arg1.mult_ops() + arg2.mult_ops()+1;
        }
        //////////////////////
    };

    /** sum expression*/
    template<typename T1, typename T2>
    constexpr expr_times<T1, T2>
    operator * (T1 arg1, T2 arg2){
        return expr_times<T1, T2 >(arg1, arg2);}
} //namespace expressions
