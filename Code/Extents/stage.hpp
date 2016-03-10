#pragma once

template <typename Functor, typename ... Args>
struct stage{
    typedef typename compute_extent<Functor>::type extent_t;

};
