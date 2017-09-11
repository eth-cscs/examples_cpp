    #include "../show.h"


/////// FACILITY SIDE
namespace facility {
    template<typename ...T>
    using void_t = void;
}

/////// LIBRARY SIDE
namespace my_library {
    namespace detail {
        template<class C>
        using can_add = decltype(std::declval<C>() + std::declval<C>());


        template<typename T, typename VOID=void> // this "void" is idiomatic
        struct sum {
            static std::string add(T const &, T const &) { throw 42; }
        };

        template<typename T>
        struct sum<T, facility::void_t < can_add<T>>> { // using the void_t idiom
            static T add(T const &a, T const &b) {
                return a + b;
            }
        };
    } // namespace detail

    template<typename T>
    void do_sum(T const &a, T const &b) {
        try {
            SHOW(detail::sum<T>::add(a, b))
        }
        catch (int ex) {
            switch (ex) {
                case 42:
                    std::cout << ex << ": No operator found\n";
            }
        }
    }

}
/////////// USER SIDE!

struct A {};

std::ostream& operator<<(std::ostream& s, A) {
    return s << "A";
}

struct B {
    std::string s;
    B(std::string s) : s{s} {}
};

B operator+(B const& x, B const& y) {return B{x.s + " " + y.s};}

std::ostream& operator<<(std::ostream& s, B const& x) {
    return s << x.s;
}

int main() {
    my_library::do_sum(3,4);
    my_library::do_sum(A{}, A{});
    my_library::do_sum(B{"Hello"}, B{"world!"});
}
