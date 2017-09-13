#pragma once

namespace expressions{

    template <typename T1>
    struct expand_derivative;

    template <typename T1>
    constexpr auto
    D (T1 arg1){
        return expand_derivative<T1>(arg1)();
    }

    template<typename T>
    struct expand_derivative<p<T>>{

        constexpr expand_derivative(p<T>) {}

        constexpr auto operator()() const {
            return c<T>{1};
        }
    };

    template<typename U>
    struct expand_derivative<c<U>>{

        constexpr expand_derivative(c<U>) {}

        constexpr auto operator()() const{
            return c<U>{0};
        }
    };

    template <typename T1, typename T2>
    struct expand_derivative<expr_plus<T1, T2> >{

        expr_plus<T1, T2> arg1;

        constexpr expand_derivative(expr_plus<T1,T2> arg) :arg1(arg) {}

        constexpr auto operator()() const{
            return D(arg1.arg1) + D(arg1.arg2);
        }
    };

    // This specialization is not useful for the functionality, but to
    // reduce the length of the output expression
    template <typename T1, typename T>
    struct expand_derivative<expr_plus<T1, c<T> > >{

        expr_plus<T1, c<T>> arg1;

        constexpr expand_derivative(expr_plus<T1,c<T>> arg) :arg1(arg) {}

        constexpr auto operator()() const{
            return D(arg1.arg1);
        }
    };

    // This specialization is not useful for the functionality, but to
    // reduce the length of the output expression
    template <typename T, typename T2>
    struct expand_derivative<expr_plus<c<T>, T2 > >{

        expr_plus<c<T>, T2> arg1;

        constexpr expand_derivative(expr_plus<c<T>,T2> arg) :arg1(arg) {}

        constexpr auto operator()() const{
            return D(arg1.arg2);
        }
    };

    // This specialization is not useful for the functionality, but to
    // reduce the length of the output expression
    template <typename T, typename U>
    struct expand_derivative<expr_plus<c<T>, c<U> > >{
        constexpr expand_derivative(expr_plus<c<T>,c<U>>) {}

        constexpr auto operator()() const{
            return c<T>{0};
        }
    };

    template <typename T1, typename T2>
    struct expand_derivative<expr_times<T1, T2> >{

        expr_times<T1, T2> arg1;

        constexpr expand_derivative(expr_times<T1,T2> arg1) :arg1(arg1) {}

        constexpr auto operator()() const{
            return D(arg1.arg1) * arg1.arg2 + arg1.arg1 * D(arg1.arg2);
        }
    };

    // This specialization is not useful for the functionality, but to
    // reduce the length of the output expression
    template <typename T1, typename T>
    struct expand_derivative<expr_times<T1, c<T>> >{

        expr_times<T1, c<T>> arg1;

        constexpr expand_derivative(expr_times<T1,c<T>> arg1) :arg1(arg1) {}

        constexpr auto operator()() const{
            return D(arg1.arg1) * arg1.arg2;
        }
    };

    // This specialization is not useful for the functionality, but to
    // reduce the length of the output expression
    template <typename T, typename T2>
    struct expand_derivative<expr_times<c<T>, T2> >{

        expr_times<c<T>, T2> arg1;

        constexpr expand_derivative(expr_times<c<T>, T2> arg1) :arg1(arg1) {}

        constexpr auto operator()() const{
            return arg1.arg1 * D(arg1.arg2);
        }
    };

    // This specialization is not useful for the functionality, but to
    // reduce the length of the output expression
    template <typename T, typename U>
    struct expand_derivative<expr_times<c<T>, c<U>> >{

        constexpr expand_derivative(expr_times<c<T>, c<U>> ) {}

        constexpr auto operator()() const{
            return c<T>{0};
        }
    };


}//namespace expressions
