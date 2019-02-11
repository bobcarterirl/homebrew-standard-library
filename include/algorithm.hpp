#pragma once

#include <algorithm>

namespace hsl
{

using std::fill;
using std::copy;
using std::move;
using std::remove;
using std::remove_if;

template<typename II1, typename II2>
bool equal(II1 first1, II1 last1, II2 first2);

template<typename II1, typename II2>
bool lexicographical_compare(II1 first1, II1 last1, II2 first2, II2 last2);


// Template function implementations

// TODO predicate
template<typename II1, typename II2>
bool equal(II1 first1, II1 last1, II2 first2)
{
    for (; first1 != last1; ++first1, ++first2)
    {
        if (!(*first1 == *first2)) return false;
    }

    return true;
}

// TODO custom
template<typename II1, typename II2>
bool lexicographical_compare(II1 first1, II1 last1, II2 first2, II2 last2)
{
    for (; first1 != last1 && first2 != last2; ++first1, ++first2)
    {
        if (*first1 < *first2) return true;
        else if (*first2 < *first1) return false;
    }

    return first2 != last2;
}

}
