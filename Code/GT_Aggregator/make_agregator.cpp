#include <utility>

template <int I, typename Storage>
struct pair{
    static const int ID=I;
    using storage_t = Storage;
};

template <int ID, typename T>
auto&& make_pair(T t_){return std::move(pair<ID, T>());}

template <int I, typename Pair>
struct arg{};

template <typename ... Args>
struct aggregator_type{
    template <typename ... Pair>
    aggregator_type(Pair ... st_){}
};

template <typename ... Pair>
auto&& make_aggregator(Pair&& ... pair_){
    return std::move(aggregator_type< arg<Pair::ID, typename Pair::storage_t> ... > (&pair_ ...));
}

int main(){
    auto t=make_aggregator(make_pair<1>(2), make_pair<3>(5.), make_pair<2>("blah"));
    return 0;
}
