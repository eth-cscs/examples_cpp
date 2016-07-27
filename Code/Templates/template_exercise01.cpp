#include <string>
#include <iostream>
#include <type_traits>

namespace solution {
    template <typename T, typename VOID=void>
    struct bind;

    struct plh {};
    struct firstname_plh : plh {
        using type = std::string;
        using this_type = firstname_plh;

        bind<this_type> operator=(type const&);
    };

    struct lastname_plh : plh {
        using type = std::string;
        using this_type = lastname_plh;

        bind<this_type> operator=(type const&);
    };

    struct age_plh : plh {
        using type = int;
        using this_type = age_plh;

        bind<this_type> operator=(type const&);
    };

    template <typename T>
    struct bind<T, typename std::enable_if<std::is_base_of<plh, T>::value, void>::type> {
        typename T::type _data;
    };

    bind<firstname_plh::this_type> firstname_plh::operator=(firstname_plh::type const& t) {
        return bind<firstname_plh::this_type>{t};
    }

    bind<lastname_plh::this_type> lastname_plh::operator=(lastname_plh::type const& t) {
        return bind<lastname_plh::this_type>{t};
    }

    bind<age_plh::this_type> age_plh::operator=(age_plh::type const& t) {
        return bind<age_plh::this_type>{t};
    }

    firstname_plh firstname;
    lastname_plh lastname;
    age_plh age;

} // namespace solution


struct record_t {
    std::string firstname = "", lastname = "";
    int age = 0;

    template <typename... Binders>
    record_t(Binders const& ...args) {
        init_with_binders(args...);
    }

    void set_member(solution::bind<solution::firstname_plh> const& x) {
        firstname = std::move(x._data);
    }

    void set_member(solution::bind<solution::lastname_plh> const& x) {
        lastname = std::move(x._data);
    }

    void set_member(solution::bind<solution::age_plh> const& x) {
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
    auto record = record_t( lastname = "Bianco", firstname = "Mauro", age = 21 );
    std::cout << record << "\n";
}
