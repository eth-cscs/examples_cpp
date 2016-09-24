#include <tuple>

template<typename Tuple, int ... Ids>
std::array<int, sizeof...(Ids)>
create_vector(Tuple& tuple_,
              std::integer_sequence<int, Ids ...>){
  return {sizeof(std::get<Ids>(tuple_)) ...};
}

int main(){
    auto tuple_ = std::make_tuple(1., 'b', 2u, "ciao");
    create_vector(tuple_, std::make_integer_sequence<int, 4>());
}
