#include <vector>
#include <tuple>
#include <iostream>
#include <iomanip>
#include <cstdlib>

namespace stencil_stuff {

    /** Storage class for a 3D array of elements of type T
     */
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

    /** Class to specify the number of halo points to skip when
        calculating a stencil.  The stencil will be applied in points
        that are inside the array storage by the amount specified by
        the template arguments.  In this simple example the points at
        the beginning and at the end of a dimension of the array are
        the same.
     */
    template <int I, int J, int K>
    struct halo_type {
        static constexpr int i_halo = I;
        static constexpr int j_halo = J;
        static constexpr int k_halo = K;
    };

    /** Incorporating the classes and functions that are not directly
        used by the designed API into a namespace, so that the user of
        the API could not accedentally use them
     */
    namespace _detail {
        /** Since trasnforming a std::tuple into an argument pack is
            not trivial, we need to defer calling the stencil operator
            in this call class, which uses std::integer_sequence to be
            able to unpack the tuple elements containing the proxies.
         */
        template <typename, typename, typename>
        struct call;

        /** We need a specialization for extracting the integer
            indices of the std::integer_sequence as an argument pack,
            so that we can call std::get<> "variadically"
         */
        template <typename Operator, typename Proxies, int ...Is>
        struct call<Operator, Proxies, std::integer_sequence<int, Is...>> {
            void operator()(Operator op, Proxies & proxies) {
                op(std::get<Is>(proxies)...);
            }
        };

        /** This is the proxy object, focus of this exercise.  The
            proxy is supposed to act as a value in the array and
            access neighbors.  It contains a reference to the storage
            for which it is a proxy, and from which obtaining the
            offsets to access the data.
        */
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

            value_type operator()() const {
                return *m_ptr;
            }

            value_type& operator()() {
                return *m_ptr;
            }

            value_type operator()(int i, int j, int k) const {
                return *(m_ptr + m_storage.offset(i,j,k));
            }

            value_type& operator()(int i, int j, int k) {
                return *(m_ptr + m_storage.offset(i,j,k));
            }
        };

        /** The following struct is used to iterate over a tuple of
            proxies and call a proper method for each of them. Tuples
            are generally processed recursvively, since it contains
            elements of different types and the std::get<> helper
            accepts an index that is a constant value
         */
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

        /* base of the recursion */
        template <typename Tuple, std::size_t Bound>
        struct recurse<Tuple, Bound, Bound> {
            static void move(Tuple &, int, int, int) {}
            static void increment(Tuple &) {}
        };

        /** function to move the proxies to the proper point in the
            storages before starting the stencil loop
         */
        template <typename Tuple>
        void move_proxies_to(int i, int j, int k, Tuple &proxies) {
            recurse<Tuple, 0, std::tuple_size<Tuple>::value>::move(proxies, i, j, k);
        }

        /** Function to move the proxies to the next point in the
            innermost loop
         */
        template <typename Tuple>
        void increment_pointers(Tuple &proxies) {
            recurse<Tuple, 0, std::tuple_size<Tuple>::value>::increment(proxies);
        }
    } //namespace _detail

    /** This is the main API element to execute a stencil. It takes
        the stencil operator, which is a callable object with template
        arguments corresponding to the storages where the stencil is
        applied. Instead of the storage elements, we pass proxies so
        that the access to the neighbors can be effectively done by
        forwarding the appropriate calls to the storages.
     */
    template < typename Operator, int I, int J, int K, typename ...Data>
    void stencil_run(Operator op, halo_type<I,J,K>,
                     std::size_t n, std::size_t m, std::size_t l,
                     Data & ...data) {
        using namespace _detail;
        auto proxies = std::make_tuple(proxy<Data>(data)...);

        for (int i = I; i < n-I; ++i) {
            for (int j = J; j < m-J; ++j) {
                move_proxies_to(i,j,K, proxies);
                for (int k = K; k < l-K; ++k) {
                    call<Operator, decltype(proxies), std::make_integer_sequence<int,sizeof...(Data)>>()(op, proxies);
                    increment_pointers(proxies);
                }
            }
        }
    };
} // namespace stencil_stuff



int main(int argc, char** argv) {
    using namespace stencil_stuff;
    if (argc != 4) {std::terminate();}

    std::size_t n = std::atoi(argv[1]), m = std::atoi(argv[2]), l = std::atoi(argv[3]);
    std::cout << n << " " << m << " " << l << "\n\n";
    storage_type<double> in(n,m,l);
    storage_type<double> out(n,m,l);

    std::size_t i{}, j{}, k{};
    stencil_run([&i, &j, &k, n, m, l](auto & in, auto & out) {
            out(0,0,0) = 0.0;
            in(0,0,0) = (i+j+k);
            ++k;
            if (k==l) {k=0; ++j;}
            if (j==m) {j=0; ++i;}
        }, halo_type<0,0,0>(), n, m, l, in, out);

    std::cout << "***********************************\n";
    stencil_run([&i, &j, &k, n, m, l](auto & in, auto & out) {
            std::cout << std::setw(4) << in(0,0,0) << " ";
            ++k;
            if (k==l) {k=0; ++j; std::cout << "\n";}
            if (j==m) {j=0; ++i; std::cout << "\n\n";}
        }, halo_type<0,0,0>(), n, m, l, in, out);
    std::cout << "***********************************\n";

    stencil_run([](auto const& in, auto & out) {
        out(0,0,0) =  in(0,0,0) - 6.* (in(1,0,0) + in(-1,0,0)
                                      + in(0,1,0) + in(0,-1,0)
                                      + in(0,0,1) + in(0,0,-1));
        }, halo_type<1,1,1>(), n, m, l, in, out);

    std::cout << "***********************************\n";
    stencil_run([&i, &j, &k, n, m, l](auto & in, auto & out) {
            std::cout << std::setw(4) << out(0,0,0) << " ";
            ++k;
            if (k==l) {k=0; ++j; std::cout << "\n";}
            if (j==m) {j=0; ++i; std::cout << "\n\n";}
        }, halo_type<0,0,0>(), n, m, l, in, out);
    std::cout << "***********************************\n";


    bool result = true;
    for (i = 1; i < n-1; ++i) {
        for (j = 1; j < m-1; ++j) {
            for (k = 1; k < l-1; ++k) {
                auto v = in(i,j,k) - 6.* (in(i+1,j,k) + in(i-1,j,k)
                                          + in(i,j+1,k) + in(i,j-1,k)
                                          + in(i,j,k+1) + in(i,j,k-1));
                if (out(i,j,k) != v) {
                    std::cout << "Error in "
                              << i << " "
                              << j << " "
                              << k << " : "
                              << out(i,j,k) << " != "
                              << v << "\n";
                    result = false;
                }
            }
        }
    }

    if (result) {
        std::cout << "PASSED\n";
    } else {
        std::cout << "FAILED\n";
    }
}
