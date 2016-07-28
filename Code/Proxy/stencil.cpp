#include <vector>
#include <tuple>
#include <iostream>
#include <cstdlib>

template <typename T>
class storage_type {
    using uint = std::size_t;
    uint m_n, m_m, m_l;
    uint m_stride_m, m_stride_l;
    std::vector<T> m_data;
public:
    using value_type = T;

    storage_type(uint n, uint m, uint l)
        : m_n(n), m_m(m), m_l(l)
        , m_stride_m(m_m*m_l), m_stride_l(m_l)
        , m_data(m_n*m_m*m*l)

    {}

    T& operator()(uint i, uint j, uint k) {
        return m_data[offset(i,j,k)];
    }

    T operator()(uint i, uint j, uint k) const {
        return m_data[offset(i,j,k)];
    }

    int offset(int i, int j, int k) const {
        return i * m_stride_m + j * m_stride_l + k;
    }

    uint n() const {return m_n;}
    uint m() const {return m_m;}
    uint l() const {return m_l;}
};


template <int I, int J, int K>
struct halo_type {
    static constexpr int i_halo = I;
    static constexpr int j_halo = J;
    static constexpr int k_halo = K;
};


template <typename, typename, typename>
struct call;

template <typename Operator, typename Proxies, int ...Is>
struct call<Operator, Proxies, std::integer_sequence<int, Is...>> {
    void operator()(Operator op, Proxies & proxies) {
        op(std::get<Is>(proxies)...);
    }
};


template <typename StorageType>
struct proxy {
    using value_type = typename StorageType::value_type;

    StorageType & m_storage;
    value_type *m_ptr;
    proxy(StorageType & st)
        : m_storage{st}, m_ptr(nullptr)
    {}

    void set_pointer(int i, int j, int k) {
        m_ptr = &m_storage(i,j,k);
    }

    void increment() {++m_ptr;}

    value_type operator()(int i, int j, int k) const {
        return *(m_ptr + m_storage.offset(i,j,k));
    }

    value_type& operator()(int i, int j, int k) {
        return *(m_ptr + m_storage.offset(i,j,k));
    }
};

template <typename Tuple, std::size_t Index, std::size_t LoopBound>
struct recurse {
    static void move(Tuple & proxies, int i, int j, int k) {
        std::get<Index>(proxies).set_pointer(i,j,k);
        recurse<Tuple, Index+1, LoopBound>::move(proxies,i,j,k);
    }
    static void increment(Tuple & proxies) {
        std::get<Index>(proxies).increment();
        recurse<Tuple, Index+1, LoopBound>::increment(proxies);
    }
};

template <typename Tuple, std::size_t Bound>
struct recurse<Tuple, Bound, Bound> {
    static void move(Tuple & proxies, int i, int j, int k) {}
    static void increment(Tuple & proxies) {}
};

template <typename Tuple>
void move_proxies_to(int i, int j, int k, Tuple &proxies) {
    recurse<Tuple, 0, std::tuple_size<Tuple>::value>::move(proxies, i, j, k);
}

template <typename Tuple>
void increment_pointers(Tuple &proxies) {
    recurse<Tuple, 0, std::tuple_size<Tuple>::value>::increment(proxies);
}

template < typename Operator, int I, int J, int K, typename ...Data>
void stencil_run(Operator op, halo_type<I,J,K>,
                 std::size_t n, std::size_t m, std::size_t l,
                 Data & ...data) {
    auto proxies = std::make_tuple(proxy<Data>(data)...);

    for (int i = I; i < n-I; ++i) {
        for (int j = J; j < m-J; ++j) {
            move_proxies_to(i,j,0, proxies);
            for (int k = K; k < l-K; ++k) {
                call<Operator, decltype(proxies), std::make_integer_sequence<int,sizeof...(Data)>>()(op, proxies);
                increment_pointers(proxies);
            }
        }
    }
};



int main(int argc, char** argv) {
    if (argc != 4) {std::terminate();}

    std::size_t n = std::atoi(argv[1]), m = std::atoi(argv[2]), l = std::atoi(argv[3]);
    storage_type<double> in(n,m,l);
    storage_type<double> out(n,m,l);

    std::size_t i{}, j{}, k{};
    stencil_run([&i, &j, &k, n, m, l](auto & in, auto & out) {
            std::cout << i << " " << j << " " << k << "\n";
            out(0,0,0) = 0.0;
            in(0,0,0) = i+j+k;
            ++k;
            if (k==l) {k=0; ++j;}
            if (j==m) {j=0; ++i;}
        }, halo_type<0,0,0>(), n, m, l, in, out);

    stencil_run([](auto const& in, auto & out) {
        out(0,0,0) = in(0,0,0) - 6.* (in(1,0,0) + in(-1,0,0)
                                      + in(0,1,0) + in(0,-1,0)
                                      + in(0,0,1) + in(0,0,-1));
        }, halo_type<1,1,1>(), n, m, l, in, out);

}
