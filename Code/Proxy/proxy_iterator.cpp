#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

template <typename It0, typename It1>
struct zip_proxy {

    std::pair<It0, It1> m_zip;

    zip_proxy(It0 it0, It1 it1)
        : m_zip(it0,it1)
    {}

    // The dereferencin operator returns the pair of iterators. This
    // pair is not assumed to be changed, since that would mean to
    // change the contaiing iterators, and that would basically break
    // the semantics of the zipping. So we return now the pair as a
    // value.
    std::pair<It0, It1> operator*() const {
        return m_zip;
    }

    // Advancing both iterators
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
    std::list<float> fv = {7, 6, 5, 4, 3, 2, 1};

    auto zip0 = make_zip_proxy(iv.begin(), fv.begin());
    auto zip1 = make_zip_proxy(iv.end(), fv.end());

    std::for_each(zip0, zip1, [](auto x) {*(x.first) += *(x.second); *(x.second) *= 2;});
    std::for_each(zip0, zip1, [](auto const x) {std::cout << (*(x.first))++ << ", " << (*(x.second))++ << "\n";});

    std::for_each(make_zip_proxy(iv.cbegin(), fv.cbegin()), make_zip_proxy(iv.cend(), fv.cend()),
                  [](auto const x) {std::cout << "\"" << *(x.first) << ", " << *(x.second) << "\"\n";});

}
