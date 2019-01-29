#pragma once

#include "cstddef.hpp"
#include "algorithm.hpp"
#include "iterator.hpp"     // hsl::begin, hsl::end defined here
#include "stdexcept.hpp"
#include "tuple.hpp"
#include "type_traits.hpp"
#include "utility.hpp"

namespace hsl
{

template<typename T, size_t N>
class array
{
private:
    struct EmptyArray {};
    using Array = hsl::conditional_t<N, T[N], EmptyArray>;


public:
    using value_type             = T;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using pointer                = value_type*;
    using const_pointer          = const value_type*;
    using iterator               = pointer;
    using const_iterator         = const_pointer;
    using reverse_iterator       = hsl::reverse_iterator<iterator>;
    using const_reverse_iterator = hsl::reverse_iterator<const_iterator>;
    using size_type              = size_t;
    using difference_type        = ptrdiff_t;


    // Must be public for aggregate initialization to work.
    // Don't access it directly; use data() method, instead.
    Array arr;


    // Iterators
    constexpr iterator begin() noexcept
    {
        if constexpr (N) return hsl::begin(arr);
        else return iterator(nullptr);
    }

    constexpr const_iterator begin() const noexcept
    {
        if constexpr (N) return hsl::begin(arr);
        else return const_iterator(nullptr);
    }

    constexpr iterator end() noexcept
    {
        if constexpr (N) return hsl::end(arr);
        else return iterator(nullptr);
    }

    constexpr const_iterator end() const noexcept
    {
        if constexpr (N) return hsl::end(arr);
        else return iterator(nullptr);
    }

    constexpr const_iterator cbegin() const noexcept
    {
        if constexpr (N) return hsl::cbegin(arr);
        else return const_iterator(nullptr);
    }

    constexpr const_iterator cend() const noexcept
    {
        if constexpr (N) return hsl::cend(arr);
        else return const_iterator(nullptr);
    }

    constexpr reverse_iterator rbegin() noexcept
    {
        if constexpr (N) return hsl::rbegin(arr);
        else return reverse_iterator(nullptr);
    }

    constexpr const_reverse_iterator rbegin() const noexcept
    {
        if constexpr (N) return hsl::rbegin(arr);
        else return const_reverse_iterator(nullptr);
    }

    constexpr reverse_iterator rend() noexcept
    {
        if constexpr (N) return hsl::rend(arr);
        else return reverse_iterator(nullptr);
    }

    constexpr const_reverse_iterator rend() const noexcept
    {
        if constexpr (N) return hsl::rend(arr);
        else return const_reverse_iterator(nullptr);
    }

    constexpr const_reverse_iterator crbegin() const noexcept
    {
        if constexpr (N) return hsl::crbegin(arr);
        else return const_reverse_iterator(nullptr);
    }

    constexpr const_reverse_iterator crend() const noexcept
    {
        if constexpr (N) return hsl::crend(arr);
        else return const_reverse_iterator(nullptr);
    }


    // Capacity
    constexpr size_t size() const noexcept
    {
        return N;
    }

    constexpr size_t max_size() const noexcept
    {
        return N;
    }

    constexpr bool empty() const noexcept
    {
        if constexpr (N) return false;
        else return true;
    }


    // Element access
    constexpr T& operator[] (size_t n)
    {
        if constexpr (N) return arr[n];
        else return *static_cast<T*>(nullptr);
    }

    constexpr const T& operator[] (size_t n) const
    {
        if constexpr (N) return arr[n];
        else return *static_cast<T*>(nullptr);
    }

    constexpr T& at(size_t n)
    {
        if constexpr (N)
        {
            if (n < N) return arr[n];
        }
        throw out_of_range("hsl::array::at");
    }

    constexpr const T& at(size_t n) const
    {
        if constexpr (N)
        {
            if (n < N) return arr[n];
        }
        throw out_of_range("hsl::array::at");
   }

    constexpr T& front()
    {
        if constexpr (N) return arr[0];
        else return *static_cast<T*>(nullptr);
    }

    constexpr const T& front() const
    {
        if constexpr (N) return arr[0];
        else return *static_cast<T*>(nullptr);
    }

    constexpr T& back()
    {
        if constexpr (N) return arr[N - 1];
        else return *static_cast<T*>(nullptr);
    }

    constexpr const T& back() const
    {
        if constexpr (N) return arr[N - 1];
        else return *static_cast<T*>(nullptr);
    }

    constexpr T* data() noexcept
    {
        if constexpr (N) return arr;
        else return nullptr;
    }

    constexpr const T* data() const noexcept
    {
        if constexpr (N) return arr;
        else return nullptr;
    }


    // Operations
    void fill(const T& val)
    {
        hsl::fill(begin(), end(), val);
    }

    void swap(array<T, N>& other)
    noexcept(is_nothrow_swappable<T>::value)
    {
        hsl::swap(arr, other.arr);
    }
};
 

// Tuple helper class specializations

template<size_t I, typename T, size_t N>
struct tuple_element<I, array<T, N> >
{
    using type = T;
};

template<typename T, size_t N>
struct tuple_size<array<T, N> > : public integral_constant<size_t, N> {};


// Template non-member function

// Relational operators

template<typename T, size_t N>
bool operator== (const array<T, N>& lhs, const array<T, N>& rhs)
{
    return equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<typename T, size_t N>
bool operator< (const array<T, N>& lhs, const array<T, N>& rhs)
{
    return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<typename T, size_t N>
bool operator!= (const array<T, N>& lhs, const array<T, N>& rhs) { return !(lhs == rhs); }

template<typename T, size_t N>
bool operator<= (const array<T, N>& lhs, const array<T, N>& rhs) { return !(rhs < lhs); }

template<typename T, size_t N>
bool operator> (const array<T, N>& lhs, const array<T, N>& rhs) { return rhs < lhs; }

template<typename T, size_t N>
bool operator>= (const array<T, N>& lhs, const array<T, N>& rhs) { return !(lhs < rhs); }


// Tuple-style get

template<size_t I, typename T, size_t N>
constexpr T& get(array<T, N>& arr) noexcept
{
    static_assert(I < N, "I must be less than N");
    return arr[I];
}

template<size_t I, typename T, size_t N>
constexpr T& get(array<T, N>&& arr) noexcept
{
    static_assert(I < N, "I must be less than N");
    return arr[I];
}

template<size_t I, typename T, size_t N>
constexpr const T& get(const array<T, N>& arr) noexcept
{
    static_assert(I < N, "I must be less than N");
    return arr[I];
}


// Swap specialization

template<typename T, size_t N>
constexpr void swap(array<T, N>& lhs, array<T, N>& rhs)
noexcept(noexcept(lhs.swap(rhs)))
{
    lhs.swap(rhs);
}

}
