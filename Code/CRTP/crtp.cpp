#include <iostream>
#include <chrono>


namespace runtime {
    class base {

        std::string m_name;
        int m_count;
    public:
        base(std::string n) : m_name(n), m_count(0) {}

        std::string const& name() const {return m_name;}

        virtual void print_me() const = 0;

        virtual void inc() = 0;
    };


    class derived_i: public base {

        int m_value;
    public:
        derived_i(std::string n, int v)
            : base(n)
            , m_value(v)
        {}

        virtual void print_me() const {
            std::cout << "Derived >"
                      <<  name()
                      << "< value: "
                      << m_value
                      << std::endl;
        }

        virtual void inc() {
            ++m_value;
        }
    };


    class derived_c: public base {

        double m_a, m_b;
    public:
        derived_c(std::string n, float a, float b)
            : base(n)
            , m_a(a)
            , m_b(b)
        {}

        virtual void print_me() const {
            std::cout << "Derived >"
                      <<  name()
                      << "< value: ("
                      << m_a << " + i" << m_b << ")"
                      << std::endl;
        }

        virtual void inc() {
            m_a = m_a + 1;
            m_b = m_b + 1;
        }
    };

    inline void run(base & d, const int N) {
        auto start = std::chrono::high_resolution_clock::now();
        for (volatile int i = 0; i < N; ++i) {
            d.inc();
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end-start;
        std::cout << "Time: " << diff.count() << std::endl;
    }

} // namespace runtime

namespace compiletime {

    template <typename Derived>
    class base {

        std::string m_name;
    public:
        base(std::string n) : m_name(n) {}

        std::string const& name() const {return m_name;}

        void print_me() const {
            static_cast<Derived*>(this)->print_me();
        }

        void inc() {
            static_cast<Derived*>(this)->inc();
        }
    };

    class derived_i: public base<derived_i> {
        using base_type = base<derived_i>;

        int m_value;
    public:
        derived_i(std::string n, int v)
            : base_type(n)
            , m_value(v)
        {}

        virtual void print_me() const {
            std::cout << "Derived >"
                      << base_type::name()
                      << "< value: "
                      << m_value
                      << std::endl;
        }

        virtual void inc() {
            ++m_value;
        }
    };

    class derived_c: public base<derived_c> {
        using base_type = base<derived_c>;

        double m_a, m_b;
    public:
        derived_c(std::string n, float a, float b)
            : base_type(n)
            , m_a(a)
            , m_b(b)
        {}

        virtual void print_me() const {
            std::cout << "Derived >"
                      <<  name()
                      << "< value: ("
                      << m_a << " + i" << m_b << ")"
                      << std::endl;
        }

        virtual void inc() {
            m_a = m_a + 1;
            m_b = m_b + 1;
        }
    };

    template <typename T>
    inline void run(T & d, const int N) {
        auto start = std::chrono::high_resolution_clock::now();
        for (volatile int i = 0; i < N; ++i) {
            d.inc();
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end-start;
        std::cout << "Time: " << diff.count() << std::endl;
    }


} // namespace compiletime


int main(int argc, char** argv) {

    const int N = atoi(argv[1]);
    {
        compiletime::derived_i d("derived_i compiletime", 666);

        d.print_me();


        compiletime::run(d, N);

        d.print_me();
    }

    std::cout << std::endl;

    {
        compiletime::derived_c c("derived_c compiletime", 1.0, 2.0);

        c.print_me();

        compiletime::run(c, N);

        c.print_me();
    }

    std::cout << std::endl;


    {
        runtime::derived_c c("derived_c runtime", 1.0, 2.0);

        c.print_me();

        runtime::run(c, N);

        c.print_me();
    }

    std::cout << std::endl;


    {
        runtime::derived_i d("derived_i runtime", 666);

        d.print_me();

        runtime::run(d, N);

        d.print_me();
    }


    std::cout << std::endl;

    return 0;
}
