    template<int Index, typename Coord>
    constexpr int idx_impl(std::integer_sequence< int, Index > , Coord coord_) const{
        return coord_;
    }
