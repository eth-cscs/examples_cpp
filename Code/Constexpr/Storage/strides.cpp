template<int CurK, int ... RestK
         , typename CurC, typename ... RestC>
constexpr int idx_impl(std::integer_sequence< int,  CurK, RestK ... >
                       , CurC first_coord_ , RestC ... coords_) const {
    return first_coord_
        + m_dims[CurK]
        * idx_impl(std::integer_sequence<int, RestK ...>(), coords_ ...);
}
