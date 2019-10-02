#include <iostream>

using uint = unsigned int;

/**
   A compile time sequence of values of type T
 */
template <typename T, T ...Vs>
struct s_vector {
    using value_type = T;
    static constexpr uint size = sizeof...(Vs);
};

/**
   Metafunction to concatenate to s_vectors
 */
template <typename S1, typename S2>
struct concat;

template <typename T, T... s0, T... s1>
struct concat<s_vector<T, s0...>, s_vector<T, s1...>> {
    using type = s_vector<T, s0..., s1...>;
};

/**
   Function to print recursively the content fo an s_vector,
   but actually it would work for any variadic pack of
   values of the same type
 */
template <typename T>
void out(std::ostream& s, T F) {
    s << F;
}

template <typename T, typename ...Ts>
void out(std::ostream& s, T F, Ts... Vs) {
    s << F << ", ";
    out(s, Vs...);
}

/**
   Function to print an s_vector
 */
template <typename T, T ...Vs>
std::ostream& operator<<(std::ostream& s, s_vector<T, Vs...>) {
    s << "s_vector<";
    out(s, Vs...);
    s << ">";
    return s;
}


/**
   Meta-function to access an element of an s_vector.
   This is far more general, it works with any container
   that has takes the type and the sequence of values
   as variadic pack, plus a ::size member.
 */
template <typename Seq, uint Index>
struct at {
    static_assert(Seq::size > Index, "Out of bound");

    template <typename S, uint Current, uint Final>
    struct search;

    template <template <typename, typename Seq::value_type...> class S,
              typename Seq::value_type First,
              typename Seq::value_type ...Vs,
              uint Current,
              uint I>
    struct search< S<typename  Seq::value_type, First, Vs...>, Current, I> {
        static constexpr typename Seq::value_type value = search< S<typename  Seq::value_type, Vs...>, Current+1, I>::value;
    };

    template <template <typename, typename Seq::value_type...> class S,
              typename Seq::value_type First,
              typename Seq::value_type ...Vs,
              uint Current>
    struct search< S<typename  Seq::value_type, First, Vs...>, Current, Current> {
        static constexpr typename Seq::value_type value = First;
    };

    static constexpr typename Seq::value_type value = search<Seq, 0u, Index>::value;
};


/**
   Meta-function to get an s_vector that is a sorted version of the
   input s_vector. It would not be difficult to generalize it to get a
   sequence which is an instantiation of the Input template, but it's
   already complicated enough.
 */
template <typename Input>
struct merge_sort {

    /**
       Meta-function to perform a selecion of type based on a boolean
       value
     */
    template <bool TakeFirst, typename S0, typename>
    struct pickfirst {
        using type = S0;
    };

    template <typename S0, typename S1>
    struct pickfirst<false, S0, S1> {
        using type = S1;
    };

    /**
       Meta-function to perform the merge of two sorted sequences.
    */
    template <typename S0, typename S1>
    struct merge;

    /**
       Meta-function to perform the merge of two sorted sequences.

       This is the case in which both sequences are not empty. We then
       take the minimum of the fron values and concatentate with the
       merge of the rest.
     */
    template <template <typename T, T... > class Seq,
              typename Input::value_type F0,
              typename Input::value_type ...V0s,
              typename Input::value_type F1,
              typename Input::value_type ...V1s>
              struct merge<Seq<typename Input::value_type, F0, V0s...>,
                           Seq<typename Input::value_type, F1, V1s...> > {
        using type = typename pickfirst<(F0<F1),
            typename concat<Seq<typename Input::value_type, F0>,
                            typename merge<Seq<typename Input::value_type,V0s...>,
                                           Seq<typename Input::value_type,F1, V1s...>
                                           >::type >::type,
            typename concat<Seq<typename Input::value_type, F1>,
                            typename merge<Seq<typename Input::value_type,F0, V0s...>,
                                           Seq<typename Input::value_type, V1s...>
                                           >::type >::type
            >::type;
    };


    /**
       Meta-function to perform the merge of two sorted sequences.

       Speciaization for when the first sequence is empty
     */
    template <template <typename T, T... > class Seq,
              typename Input::value_type ...V1s>
              struct merge<Seq<typename Input::value_type >,
                           Seq<typename Input::value_type, V1s...> > {
        using type = Seq<typename Input::value_type, V1s...>;
    };


    /**
       Meta-function to perform the merge of two sorted sequences.

       Speciaization for when the second sequence is empty
     */
    template <template <typename T, T... > class Seq,
              typename Input::value_type ...V0s>
    struct merge<Seq<typename Input::value_type, V0s... >,
                 Seq<typename Input::value_type> > {
        using type = Seq<typename Input::value_type, V0s...>;
    };


    /**
       Recursive splitting and merging
     */
    template <typename In, uint Low, uint Hi, typename Void=void>
    struct sort_chunk {
        static const uint Split = (Hi+Low+1) >> 1;
        using type = typename merge< typename sort_chunk<In, Low, Split>::type,
                                     typename sort_chunk<In, Split+1, Hi>::type>::type;
    };

    /**
       Recursive splitting and merging. Case of the size two in which
       there is the comare&swap
     */
    template <typename In, uint Low, uint Hi>
    struct sort_chunk<In, Low, Hi, typename std::enable_if< Hi-Low==1 >::type > {
        template <bool b, typename In::value_type l, typename In::value_type h>
            struct swap_if;

        template <typename In::value_type l, typename In::value_type h>
            struct swap_if<true, l, h> {
            using type = s_vector<typename In::value_type, h, l>;
        };

        template <typename In::value_type l, typename In::value_type h>
            struct swap_if<false, l, h> {
            using type = s_vector<typename In::value_type, l, h>;
        };

        static const typename In::value_type L = at<In, Low>::value;
        static const typename In::value_type H = at<In, Low+1>::value;
        using type = typename swap_if< (L>H), L, H>::type;
    };

    /**
       Recursive splitting and merging. Case of a size one sequence.
     */
    template <typename In, uint Low, uint Hi>
    struct sort_chunk<In, Low, Hi, typename std::enable_if< (Hi-Low==0) >::type > {
        using type = s_vector<typename In::value_type, at<In, Low>::value >;
    };

    /** Start the sorting */
    using type = typename sort_chunk<Input, 0, Input::size-1>::type;

};


int main() {
#ifdef __clang__
    using v = s_vector<int, 6,5,4,3,2,1,7>;

    std::cout << v() << "\n";

    using sv = merge_sort<v>::type;
    std::cout << "--------------\n";

    std::cout << sv() << "\n";
#else
    std::cout << "Compiler not supported\n";
#endif
}
