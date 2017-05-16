// A metafunction that finds the type in a sequence of types
// that has the biggest sizeof value



#include "../show.h"

template <bool Pred, typename T1, typename T2>
struct select_first {
    using type = T2;
};

template <typename T1, typename T2>
struct select_first<true, T1, T2> {
    using type = T1;
};


template <typename First, typename ...Ts>
struct find_max_size {
    static constexpr int _rest_size = find_max_size<Ts...>::value;
    static constexpr int value = sizeof(First)>_rest_size?sizeof(First):_rest_size;
    using type = typename select_first<(sizeof(First)>_rest_size), First, typename find_max_size<Ts...>::type>::type;
};

template <typename JustOne>
struct find_max_size<JustOne> {
    static constexpr int value = sizeof(JustOne);
    using type = JustOne;
};

int main() {
    SHOW((find_max_size<char, int, double, float>::value));
    static_assert((std::is_same<double, find_max_size<char, int, double, float>::type>::value), "not ok");
}
