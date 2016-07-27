#include <string>
#include <iostream>
#include <type_traits>

namespace solution {
    template <typename T, typename VOID=void>
    struct bind;

    struct plh {};
    struct firstname_tag {};

    struct lastname_tag {};
    struct age_tag {};


    template <typename Tag, typename ValueT>
    struct placeholder : plh {
        using value_type = ValueT;
        using this_type = placeholder<Tag, value_type>;

        bind<this_type> operator=(ValueT const& value) {
            return bind<this_type>{value};
        }
    };

    template <typename T>
    struct bind<T, typename std::enable_if<std::is_base_of<plh, T>::value, void>::type> {
        typename T::value_type _data;
    };

    placeholder<firstname_tag, std::string> firstname;
    placeholder<lastname_tag, std::string> lastname;
    placeholder<age_tag, int> age;

} // namespace solution


struct record_t {
    std::string firstname = "", lastname = "";
    int age = 0;

    template <typename... Binders>
    record_t(Binders const& ...args) {
        init_with_binders(args...);
    }

    void set_member(solution::bind<decltype(solution::firstname)> const& x) {
        firstname = std::move(x._data);
    }

    void set_member(solution::bind<decltype(solution::lastname)> const& x) {
        lastname = std::move(x._data);
    }

    void set_member(solution::bind<decltype(solution::age)> const& x) {
        age = x._data;
    }

    void init_with_binders() {}

    template <typename FirstBinder, typename ...OtherBinders>
    void init_with_binders(FirstBinder const& first, OtherBinders const& ...args) {
        set_member(first);
        init_with_binders(args...);
    }
};

std::ostream& operator<<(std::ostream &s, record_t const& x) {
    return s << "{ first: " << x.firstname << ", last: " << x.lastname << ", age: " << x.age << " }";
}


int main() {
    using namespace solution;
    auto record = record_t( lastname = "Bianco", age = 21, firstname = "Mauro" );
    std::cout << record << "\n";
}
