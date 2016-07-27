#pragma once
#include <utility>
#include <cassert>

//storage meta information
template <int Size>
struct storage_info{
    storage_info() = delete;

    template <typename ... Ints>
    constexpr storage_info(int first_, Ints ... dims_) :
        m_dims{first_, dims_ ...}
    {
        static_assert((sizeof...(Ints)+1==Size), "error");
    }

    constexpr storage_info(storage_info const& other) = default;

    static constexpr int size(){return Size;}

    template<int Coord>
    constexpr int dim() const {return m_dims[Coord];}

    template<typename ... Ints>
    constexpr int index(Ints ... idx) const {
        return compute_index(std::make_integer_sequence<int, sizeof...(Ints)>(), idx ... );
    }

    template<typename T>
    int compute_index(T) const { assert(false); }

        template<int First, int ... Indices, typename First_Int, typename ... Ints>
    constexpr int compute_index(std::integer_sequence< int,  First, Indices ... > , First_Int first_, Ints ... indices) const {
        return (sizeof...(Indices)>0)?
            first_ + m_dims[First] * compute_index(std::integer_sequence<int, Indices ...>(), indices ...)
            :
            first_;
    }

private:
    int m_dims[Size];
};

//exercise: generalization, create a layout map
