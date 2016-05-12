#pragma once
namespace expressions{

struct p{

    constexpr p(){};

    template<typename T>
    constexpr T operator() (T t_) const {
        return t_;
    }
    std::string to_string() const {

        return std::string(" x ");
    }

    //solution exercice 1
    constexpr int sum_ops() const {
        return 0;
    }
    constexpr int mult_ops() const {
        return 0;
    }
    /////////////////////
};

    constexpr auto x=p();
}
