#pragma once
#include<tuple>

template <int ... Args>
struct layout_map{
    static constexpr int length=sizeof...(Args);
    static const constexpr int layout_vector[sizeof...(Args)]={Args...};

    template <int I>
    static constexpr int at() {
        return layout_vector[ I ];
    }

    template <int I>
    static auto constexpr select(int const* dims) {
        return  dims[layout_vector[I]];
    }

    template <int I, typename ... T>
    static auto constexpr select(T & ... args) {
        return  std::get<layout_vector[I]>( std::make_tuple(args ...) );
    }
};
