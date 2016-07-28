#include <vector>
#include <tuple>

template <typename T>
class storage_type {
    std::vector<T> m_data;
    using uint = std::size_t;
    uint m_n, m_m, m_l;
    uint m_stride_m, m_stride_l;
public:
    storage_type(uint n, uint m, uint l)
        : m_n(n), m_m(m), m_l(l),
          m_stride_m(m_m*m_l), m_stride_l(m_l)
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
    void operator()(Proxies & proxies) {
        Operator()(std::get<Is>(proxies)...);
    }
};


template <typename StorageType>
struct proxy {
    StorageType & storage;
    proxy(StorageType & st)
        : storage{st}
    {}
};


template < typename Operator, int I, int J, int K, typename ...Data>
void stencil_run(halo_type<I,J,K>, Data & ...data) {
    auto proxies = std::make_tuple(proxy<Data>(data)...);

    for (int i = I; i < 10-I; ++i) {
        for (int j = J; j < 10-J; ++j) {


            for (int k = K; k < 10-K; ++k) {
                //                    Operator()(proxy(data...));
                call<Operator, decltype(proxies), std::make_integer_sequence<int,sizeof...(Data)>>()(proxies);
            }
        }
    }
};


struct laplacian {
    template <typename DataIn, typename DataOut>
    void operator()(DataIn const& in, DataOut &out) const {
        // out(0,0,0) = in(0,0,0) - 6.* (in(1,0,0) + in(-1,0,0)
        //                               + in(0,1,0) + in(0,-1,0)
        //                               = in(0,0,1) + in(0,0,-1));
    }
};


int main() {
    storage_type<double> in(10,10,10);
    storage_type<double> out(10,10,10);

    stencil_run<laplacian>(halo_type<1,1,1>(), in, out);
}
