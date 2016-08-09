#include <vector>
#include <algorithm>
#include <iostream>

template <typename It0, typename It1>
struct zip_proxy {

    It0 it0;
    It1 it1;

    zip_proxy(It0 it0, It1 it1)
        : it0(it0), it1(it1)
    {}

    std::pair<typename It0::value_type&, typename It1::value_type&> operator*() const {
        return std::pair<typename It0::value_type&, typename It1::value_type&>(*it0, *it1);
    }

    zip_proxy& operator++() {
        ++it0;
        ++it1;
        return *this;
    }

    zip_proxy const & operator++() const{
        ++it0;
        ++it1;
        return *this;
    }


};


template <typename It0, typename It1>
bool operator!=(zip_proxy<It0,It1> const& i0, zip_proxy<It0, It1> const& i1) {
    return (i0.it0 != i1.it0) and (i0.it1 != i1.it1);
}


template <typename T, typename U>
zip_proxy<T,U> make_zip_proxy(T t, U u) {
    return zip_proxy<T,U>(t,u);
}

int main() {
    std::vector<int>   iv = {1, 2, 3, 4, 5, 6};
    std::vector<float> fv = {7, 6, 5, 4, 3, 2, 1};

    auto zip0 = make_zip_proxy(iv.begin(), fv.begin());
    auto zip1 = make_zip_proxy(iv.end(), fv.end());

    std::for_each(zip0, zip1, [](auto x) {x.first++; x.second++;});
    std::for_each(zip0, zip1, [](auto x) {std::cout << x.first << ", " << x.second << "\n";});
}
