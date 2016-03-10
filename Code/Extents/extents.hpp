#pragma once

template<int Iminus=0, int Iplus=0, int Jminus=0, int Jplus=0, int Kminus=0, int Kplus=0>
struct extent{
    typedef extent<Iminus, Iplus, Jminus, Jplus, Kminus, Kplus> type;

    static const int iminus=Iminus;
    static const int iplus=Iplus;
    static const int jminus=Jminus;
    static const int jplus=Jplus;
    static const int kminus=Kminus;
    static const int kplus=Kplus;
};
