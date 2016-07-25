#pragma once
#include "storage_info.hpp"

// storage allocated on the heap
struct storage{
    template<int T>
    storage(storage_info<T> const& info_) :
        m_data(new double[info_.size()])
    {}
    ~storage(){ delete[] m_data; }

    template<typename StorageInfo, typename ... Ints>
    double operator()(StorageInfo info_, Ints ... ids){
        return m_data[info_.index(ids ...)];
    }
private:
    double* m_data;
};
