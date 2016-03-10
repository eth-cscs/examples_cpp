#pragma once

template <typename First, typename ... Extents>
struct subtract_extent{

    typedef typename subtract_extent<Extents ...>::type S;
    typedef extent<
        First::iminus   - S::iminus
        , First::iplus  - S::iplus
        , First::jminus - S::jminus
        , First::jplus  - S::jplus
        , First::kminus - S::kminus
        , First::kplus  - S::kplus> type;
};


template <typename First>
struct subtract_extent<First>{
    typedef First type;
};
