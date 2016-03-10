#pragma once

template <typename First, typename ... Extents>
struct sum_extent{

    typedef typename sum_extent<Extents ...>::type S;
    typedef extent<
        First::iminus   + S::iminus
        , First::iplus  + S::iplus
        , First::jminus + S::jminus
        , First::jplus  + S::jplus
        , First::kminus + S::kminus
        , First::kplus  + S::kplus> type;
};

template <typename First>
struct sum_extent<First>{
    typedef First type;
};
