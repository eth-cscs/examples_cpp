    template <typename ArgType1>
    struct unary_expr{
    /**@brief generic expression constructor*/
    constexpr unary_expr(ArgType1 const& first_operand)
        :
        first_operand{first_operand}
    {}

    template<typename Arg1>
    constexpr unary_expr( unary_expr<Arg1> const& other): first_operand(other.first_operand){}

    ArgType1 const first_operand;

private:
    /**@brief default empty constructor*/
    constexpr unary_expr(){}
};

    /**@brief Expression retrieving the maximum over a specific dimension*/
    template <typename ArgType1>
    struct expr_derivative : public unary_expr<ArgType1>{
        typedef unary_expr<ArgType1> super;
        constexpr expr_derivative(ArgType1 const& first_operand_):super(first_operand_){}

        constexpr expr_derivative(expr_derivative const& other_):super(other_){}

    private:
        constexpr expr_derivative(){};

    public:
        std::string to_string() const {
            return std::string(" D(") + super::first_operand.to_string() + ") ";
        }
    };

    namespace expressions{

        template <typename ArgType1>
        constexpr expr_derivative<ArgType1>
        D (ArgType1 arg1){
            return expr_derivative<ArgType1>(arg1);}


    namespace evaluation{

        // derivative evaluation
        // each operator implements its own derivative
        template <typename IterateDomain, typename ArgType1>
        static double
        constexpr
        value( expr_derivative<ArgType1> const& arg );

    }//namespace evaluation
    }//namespace expressions
