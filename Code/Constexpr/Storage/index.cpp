    template<typename ... Ints>
    constexpr int index(Ints ... coords_) const{
        return idx_impl(std::make_integer_sequence<int, sizeof...(Ints)>(), coords_ ... );
    }
