    /**@brief Expression summing two arguments*/
    template <typename ArgType1, typename ArgType2>
    struct expr_plus : public expr<ArgType1, ArgType2>{
        typedef expr<ArgType1, ArgType2> super;
        constexpr expr_plus(ArgType1 const& first_operand, ArgType2 const& second_operand):super(first_operand, second_operand){}

        template<typename Arg1, typename Arg2>
        constexpr expr_plus(expr_plus<Arg1, Arg2> const& other):super(other){}

    private:
        constexpr expr_plus(){};

    public:
        std::string to_string() const {
            return std::string("(") + super::first_operand.to_string() + " + " + super::second_operand.to_string() + std::string(")") ;
        }
        //currying and recursion (this gets inherited)
        // using to_string = concatenate<tokens::open_par, ArgType1, operation, ArgType2, tokens::closed_par>;
    };

    namespace expressions{
        /** sum expression*/
        template<typename ArgType1, typename ArgType2>
        constexpr expr_plus<ArgType1, ArgType2>
        operator + (ArgType1 arg1, ArgType2 arg2){
            return expr_plus<ArgType1, ArgType2 >(arg1, arg2);}

    namespace evaluation{
        /** plus evaluation*/
        template <typename ArgType1, typename ArgType2>
        auto static constexpr value(expr_plus<ArgType1, ArgType2> const& arg)
        {
            return value(arg.first_operand) + value(arg.second_operand);
        }


        //automatic differentiation
        /** plus derivative evaluation*/
        template <typename ArgType1, typename ArgType2>
        auto static constexpr value(expr_derivative<expr_plus<ArgType1, ArgType2> > const& arg)
        {
            return value(expr_derivative<ArgType1>(arg.first_operand.first_operand)) + value(expr_derivative<ArgType2>(arg.first_operand.second_operand));
        }

    }//namespace evaluation
    } //namespace expressions
