#pragma once
#include "layout_map.hpp"
#include <utility>

//storage meta information
template <typename Layout>
struct storage_info_sol{

    typedef Layout layout;

    template <typename ... Ints>
    constexpr storage_info_sol(int first_, Ints ... dims_) :
        m_dims{first_, dims_ ...}
    {
        static_assert((sizeof...(Ints)+1==Layout::length), "error");
    }

    constexpr storage_info_sol(storage_info_sol const& other) = default;

    static constexpr int size(){return Layout::length;}

    template<int Coord>
    constexpr int dim() const {return m_dims[Coord];}

    template<typename ... Ints>
    constexpr int index(Ints ... idx) const {
        return compute_index(std::make_integer_sequence<int, sizeof...(Ints)>(), idx ... );
    }

    template<int First, int ... Indices, typename First_Int, typename ... Ints>
    constexpr int compute_index(std::integer_sequence< int,  First, Indices ... > , First_Int first_, Ints ... indices) const {
        return Layout::template select<First>(first_, indices ...) + Layout::template select<First>(m_dims) * compute_index(std::integer_sequence<int, Indices ...>(), first_, indices ...);
    }

    //recursion anchor
    template<int First, typename First_Int, typename ... Ints>
    constexpr int compute_index(std::integer_sequence< int,  First> , First_Int first_, Ints ... indices) const {
        return Layout::template select<First>(first_, indices ...);
    }

private:
    int m_dims[Layout::length];
    constexpr storage_info_sol(){}
};

//exercise: generalization, create a layout map
