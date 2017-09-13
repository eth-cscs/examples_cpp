#pragma once
namespace expressions{

    template <typename U>
    struct p{

        using value_type = U;
        constexpr p(){};

        template<typename T>
        constexpr T operator() (T t_) const {
            return t_;
        }
        std::string to_string() const {

            return std::string(" x ");
        }

        constexpr int sum_ops() const {
            return 0;
        }
        constexpr int mult_ops() const {
            return 0;
        }
    };

    constexpr auto x=p<int>();
}
