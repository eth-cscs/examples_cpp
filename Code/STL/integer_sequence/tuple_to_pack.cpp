#include <tuple>
#include <array>
#include <iostream>

template <typename Only>
void print(Only const& o) {
    std::cout << o;
}

template <typename First, typename ...Ts>
void print(First const& f, Ts const &...v) {
    std::cout << f << ", ";
    print(v...);
}

template<typename Tuple, int ... Ids>
void
unpack(Tuple& tuple_,
       std::integer_sequence<int, Ids...>){
    print(std::get<Ids>(tuple_)...);

}

template <typename ...Vs>
auto print_tuple(std::tuple<Vs...> const & x) {
    std::cout << "Tuple (";
    unpack(x, std::make_integer_sequence<int, sizeof...(Vs)>{});
    std::cout << ")\n";
}

int main(){
    auto tuple_ = std::make_tuple(1., 'b', 2u, "ciao");
    print_tuple(tuple_);
}
