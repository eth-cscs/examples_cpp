// A metafunction that finds the type in a sequence of types
// that has the biggest sizeof value



#include "../show.h"
#include <type_traits>

namespace max_size {
    template <bool Pred, typename T1, typename T2>
    struct select_first {
        static_assert(true, "Something very bad happened");
    };

    template <typename T1, typename T2>
    struct select_first<false, T1, T2> {
        using type = T2;
    };

    template <typename T1, typename T2>
    struct select_first<true, T1, T2> {
        using type = T1;
    };


    template <typename First, typename ...Ts>
    struct find_max_size {
        using rest_t = typename find_max_size<Ts...>::type;
        static constexpr int _rest_size = sizeof(rest_t);
        using type = typename select_first<(sizeof(First)>_rest_size), First, rest_t>::type;
    };

    template <typename JustOne>
    struct find_max_size<JustOne> {
        using type = JustOne;
    };
} // namespace max_size

template <bool WithRef>
typename max_size::select_first<WithRef, int&, int>::type
with_ref (typename max_size::select_first<WithRef, int&, int>::type x) {
    x += 1;
    return x;
}


int main() {
    static_assert((std::is_same<double, max_size::find_max_size<char, int, double, float>::type>::value), "not ok");

    alignas(std::alignment_of<max_size::find_max_size<int, char, double>::type>::value) int x = 1;

    SHOW(x);
    SHOW((with_ref<true>(x)));
    SHOW(x);
    SHOW((with_ref<false>(x)));
    SHOW(x);
}
