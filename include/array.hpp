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
public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using iterator = T*;
    using const_iterator = const T*;
    using reverse_iterator = hsl::reverse_iterator<T*>;
    using const_reverse_iterator = hsl::reverse_iterator<const T*>;
    using size_type = size_t;
    using difference_type = ptrdiff_t;


    // Must be public for aggregate initialization to work.
    // Don't access it directly; use data() method, instead.
    T arr[N];


    // Iterators
    constexpr T* begin() noexcept { return arr; }
    constexpr const T* begin() const noexcept { return arr; }

    constexpr T* end() noexcept { return arr+N; }
    constexpr const T* end() const noexcept { return arr+N; }

    constexpr const T* cbegin() const noexcept { return arr; }
    constexpr const T* cend() const noexcept { return arr+N; }

    constexpr hsl::reverse_iterator<T*> rbegin() noexcept { return hsl::reverse_iterator<T*>(end()); }
    constexpr hsl::reverse_iterator<const T*> rbegin() const noexcept { return hsl::reverse_iterator<const T*>(end()); }

    constexpr hsl::reverse_iterator<T*> rend() noexcept { return hsl::reverse_iterator<T*>(begin()); }
    constexpr hsl::reverse_iterator<const T*> rend() const noexcept { return hsl::reverse_iterator<const T*>(begin()); }

    constexpr hsl::reverse_iterator<const T*> crbegin() const noexcept { return hsl::reverse_iterator<const T*>(end()); }
    constexpr hsl::reverse_iterator<const T*> crend() const noexcept { return hsl::reverse_iterator<const T*>(begin()); }


    // Capacity
    constexpr size_t size() const noexcept { return N; }
    constexpr size_t max_size() const noexcept { return N; }
    constexpr bool empty() const noexcept { return !N; }


    // Element access
    constexpr T& operator[] (size_t n) { return arr[n]; }
    constexpr const T& operator[] (size_t n) const { return arr[n]; }

    constexpr T& at(size_t n)
    {
        if (n >= N) throw out_of_range("hsl::array::at");
        return arr[n];
    }

    constexpr const T& at(size_t n) const
    {
        if (n >= N) throw out_of_range("hsl::array::at");
        return arr[n];
    }

    constexpr T& front() { return arr[0]; }
    constexpr const T& front() const { return arr[0]; }

    constexpr T& back() { return arr[N-1]; }
    constexpr const T& back() const { return arr[N-1]; }

    constexpr T* data() noexcept { return arr; }
    constexpr const T* data() const noexcept { return arr; }


    // Modifiers
    void fill(const T& val) { for (auto& x : arr) x = val; }
    void swap(array<T, N>& other) noexcept(is_nothrow_swappable<T>::value)
    {
        for (auto it1 = begin(), it2 = other.begin(); it1 != end(); ++it1, ++it2)
        {
            hsl::swap(*it1, *it2);
        }
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

}
