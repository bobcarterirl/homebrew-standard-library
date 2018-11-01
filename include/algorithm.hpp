#pragma once

namespace std
{
    // TODO predicate
    template<typename T1, typename T2>
    bool equal(T1 first1, T1 last1, T2 first2)
    {
        for (; first1 != last1; first1++, first2++)
        {
            if (!(*first1 == *first2)) return false;
        }

        return true;
    }

    // TODO custom
    template<typename T1, typename T2>
    bool lexographical_compare(T1 first1, T1 last1, T2 first2, T2 last2)
    {
        for (; first1 != last1 && first2 != last2; first1++, first2++)
        {
            if (*first1 < *first2) return true;
            else if (*first2 < *first1) return false;
        }

        return first2 != last2;
    }
}
