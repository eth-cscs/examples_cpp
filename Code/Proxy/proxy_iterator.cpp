#include <vector>
#include <algorithm>
#include <iostream>

template <typename It0, typename It1>
struct zip_proxy {

    std::pair<It0, It1> m_zip;


    zip_proxy(It0 it0, It1 it1)
        : m_zip(it0,it1)
    {}

    std::pair<const It0, const It1> operator*() const {
        return m_zip;
    }

    std::pair<It0, It1>& operator*() {
        return m_zip;
    }

    zip_proxy& operator++() {
        ++(m_zip.first);
        ++(m_zip.second);
        return *this;
    }

};


template <typename It0, typename It1>
bool operator!=(zip_proxy<It0,It1> const& i0, zip_proxy<It0, It1> const& i1) {
    return ((*i0).first != (*i1).first) and ((*i0).second != (*i1).second);
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

    std::for_each(zip0, zip1, [](auto& x) {*x.first += *x.second; *x.second *= 2;});
    std::for_each(zip0, zip1, [](auto x) {std::cout << *x.first << ", " << *x.second << "\n";});

}
