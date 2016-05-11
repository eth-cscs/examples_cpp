#pragma once

struct p{

    constexpr p(){};

    template<typename T>
    constexpr T operator() (T t_) const {
        return t_;
    }
    std::string to_string() const {

        return std::string(" x ");
    }
};
namespace expressions{
    constexpr auto x=p();
}
