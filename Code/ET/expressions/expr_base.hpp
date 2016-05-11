#pragma once
    // struct tokens{
    //     static  const char constexpr par_o[]="(";
    //     static const char constexpr par_c[]=")";
    //     using  open_par = string_c<print, par_o>;
    //     using  closed_par = string_c<print, par_c>;
    // };

// const constexpr char tokens::par_o[];
// const constexpr char tokens::par_c[];
    /** \section expressions Expressions Definition
        @{
        This is the base class of a binary expression, containing the instances of the two arguments.
        The expression should be a static constexpr object, instantiated once for all at the beginning of the run.
    */
    template <typename First, typename Second>
    struct expr{

        /**@brief generic expression constructor*/
        constexpr expr(First const& first_ , Second const& second_)
            :
            first_operand(first_)
            , second_operand(second_)
        {}

        template<typename Arg1, typename Arg2>
        constexpr expr(expr < Arg1, Arg2 > const& other) :
            first_operand(other.first_operand)
            , second_operand(other.second_operand)
        {}

        First const first_operand;
        Second const second_operand;

    private:
        /**@brief default empty constructor*/
        constexpr expr(){}
    };

template <typename ArgType1>
struct expr_derivative;
