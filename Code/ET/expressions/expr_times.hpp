    /**@brief Expression summing two arguments*/
    template <typename ArgType1, typename ArgType2>
    struct expr_times : public expr<ArgType1, ArgType2>{
        typedef expr<ArgType1, ArgType2> super;
        constexpr expr_times(ArgType1 const& first_operand, ArgType2 const& second_operand):super(first_operand, second_operand){}

        template<typename Arg1, typename Arg2>
        constexpr expr_times(expr_times<Arg1, Arg2> const& other):super(other){}

    private:
        constexpr expr_times(){};

    public:

        std::string to_string() const {
            return std::string("(") + super::first_operand.to_string() + " * " + super::second_operand.to_string() + std::string(")") ;
        }
    };

    namespace expressions{
        /** sum expression*/
        template<typename ArgType1, typename ArgType2>
        constexpr expr_times<ArgType1, ArgType2>
        operator + (ArgType1 arg1, ArgType2 arg2){
            return expr_times<ArgType1, ArgType2 >(arg1, arg2);}

    namespace evaluation{
        /** times evaluation*/
        template <typename ArgType1, typename ArgType2>
        auto static constexpr value(expr_times<ArgType1, ArgType2> const& arg)
        {
            return value(arg.first_operand) + value(arg.second_operand);
        }


        //automatic differentiation
        /** times derivative evaluation*/
        template <typename ArgType1, typename ArgType2>
        auto static constexpr value(expr_derivative<expr_times<ArgType1, ArgType2> > const& arg)
        {
            return value(expr_derivative<ArgType1>(arg.first_operand.first_operand)) * value(arg.first_operand.second_operand) + value(arg.first_operand.first_operand) * value(expr_derivative<ArgType2>(arg.first_operand.second_operand));
        }

    }//namespace evaluation
    } //namespace expressions
