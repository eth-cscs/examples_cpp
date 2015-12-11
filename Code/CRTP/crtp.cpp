#include <iostream>
#include <chrono>


namespace runtime {
    class base {

        int m_count;
    public:
        base() : m_count(0) {}

        virtual void print_me() const = 0;

        virtual void inc() = 0;
    };


    class derived_i: public base {

        int m_value;
    public:
        derived_i(int v)
            : base()
            , m_value(v)
        {}

        virtual void print_me() const {
            std::cout << "Derived >"
                      << "< value: "
                      << m_value
                      << std::endl;
        }

        virtual void inc() {
            m_value=m_value*m_value/100000;
        }
    };


    class derived_c: public base {

        double m_a, m_b;
    public:
        derived_c(float a, float b)
            : base()
            , m_a(a)
            , m_b(b)
        {}

        virtual void print_me() const {
            std::cout << "Derived >"
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

    public:
        base()
        {}

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
        derived_i(int v)
            : base_type()
            , m_value(v)
        {}

        void print_me() const {
            std::cout << "Derived >"
                      << "< value: "
                      << m_value
                      << std::endl;
        }

        void inc() {
            m_value=m_value*m_value/100000;
        }
    };

    class derived_c: public base<derived_c> {
        using base_type = base<derived_c>;

        double m_a, m_b;
    public:
        derived_c(float a, float b)
            : base_type()
            , m_a(a)
            , m_b(b)
        {}

        void print_me() const {
            std::cout << "Derived >"
                      << "< value: ("
                      << m_a << " + i" << m_b << ")"
                      << std::endl;
        }

        void inc() {
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
        compiletime::derived_c c(1.0, 2.0);

        c.print_me();

        compiletime::run(c, N);

        c.print_me();
    }

    std::cout << std::endl;

    {
        compiletime::derived_i d( 666);

        d.print_me();


        compiletime::run(d, N);

        d.print_me();
    }

    std::cout << std::endl;


    {
        runtime::base* c;
        const int Cond = atoi(argv[2]);
        if(Cond==0)
            c = new runtime::derived_c( 1.0, 2.0 );
        else
            c = new runtime::derived_i( 666 );

        c->print_me();

        runtime::run(*c, N);

        c->print_me();
    }

    std::cout << std::endl;

    return 0;
}
