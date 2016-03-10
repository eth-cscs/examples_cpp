#pragma once
#include <boost/mpl/int.hpp>

template<typename Iminus = boost::mpl::int_<0>
         , typename Iplus = boost::mpl::int_<0>
         , typename Jminus = boost::mpl::int_<0>
         , typename Jplus = boost::mpl::int_<0>
         , typename Kminus = boost::mpl::int_<0>
         , typename Kplus = boost::mpl::int_<0>>
struct extent{
    typedef extent<Iminus, Iplus, Jminus, Jplus, Kminus, Kplus> type;
    // typedef extent<typename Iminus::type, typename Iplus::type, typename Jminus::type, typename Jplus::type, typename Kminus::type, typename Kplus::type> type;
};

template<int Id, typename T>
struct arg;

template<typename Iminus, typename Iplus, typename Jminus, typename Jplus, typename Kminus, typename Kplus>
struct arg< 0, extent <Iminus, Iplus, Jminus, Jplus, Kminus, Kplus> >{
    typedef Iminus type;
    static const int value = Iminus::value;
};

template<typename Iminus, typename Iplus, typename Jminus, typename Jplus, typename Kminus, typename Kplus>
struct arg<1, extent <Iminus, Iplus, Jminus, Jplus, Kminus, Kplus> >{
    typedef Iplus type;
    static const int value = Iplus::value;
};

template<typename Iminus, typename Iplus, typename Jminus, typename Jplus, typename Kminus, typename Kplus>
struct arg<2, extent <Iminus, Iplus, Jminus, Jplus, Kminus, Kplus> >{
    typedef Jminus type;
    static const int value = Jminus::value;
};

template<typename Iminus, typename Iplus, typename Jminus, typename Jplus, typename Kminus, typename Kplus>
struct arg<3, extent <Iminus, Iplus, Jminus, Jplus, Kminus, Kplus> >{
    typedef Jplus type;
    static const int value = Jplus::value;
};

template<typename Iminus, typename Iplus, typename Jminus, typename Jplus, typename Kminus, typename Kplus>
struct arg<4, extent <Iminus, Iplus, Jminus, Jplus, Kminus, Kplus> >{
    typedef Kminus type;
    static const int value = Kminus::value;
};

template<typename Iminus, typename Iplus, typename Jminus, typename Jplus, typename Kminus, typename Kplus>
struct arg<5, extent <Iminus, Iplus, Jminus, Jplus, Kminus, Kplus> >{
    typedef Kplus type;
    static const int value = Kplus::value;
};
