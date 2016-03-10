#pragma once
#include "stencil.hpp"
#include "stage.hpp"

template<typename ... Stages>
stencil<Stages ...> make_stencil( Stages ... ){
    return stencil<Stages ...>();
}

template< typename Functor,
         typename ... Args>
 stage<Functor, Args ...>
make_stage( Args ... args_){
    typedef stage<Functor, Args ...> stage_t;
    return stage_t();
}
