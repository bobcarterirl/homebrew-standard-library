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
    constexpr T* begin() noexcept;
    constexpr const T* begin() const noexcept;

    constexpr T* end() noexcept;
    constexpr const T* end() const noexcept;

    constexpr const T* cbegin() const noexcept;
    constexpr const T* cend() const noexcept;

    constexpr hsl::reverse_iterator<T*> rbegin() noexcept;
    constexpr hsl::reverse_iterator<const T*> rbegin() const noexcept;

    constexpr hsl::reverse_iterator<T*> rend() noexcept;
    constexpr hsl::reverse_iterator<const T*> rend() const noexcept;

    constexpr hsl::reverse_iterator<const T*> crbegin() const noexcept;
    constexpr hsl::reverse_iterator<const T*> crend() const noexcept;


    // Capacity
    constexpr size_t size() const noexcept;
    constexpr size_t max_size() const noexcept;
    constexpr bool empty() const noexcept;


    // Element access
    constexpr T& operator[] (size_t n);
    constexpr const T& operator[] (size_t n) const;

    constexpr T& at(size_t n);
    constexpr const T& at(size_t n) const;

    constexpr T& front();
    constexpr const T& front() const;

    constexpr T& back();
    constexpr const T& back() const;

    constexpr T* data() noexcept;
    constexpr const T* data() const noexcept;


    // Modifiers
    void fill(const T& val);
    void swap(array<T, N>& other) noexcept(is_nothrow_swappable<T>::value);
};


// Tuple helper class specializations

template<size_t I, typename T, size_t N>
struct tuple_element<I, array<T, N> >
{
    using type = T;
};

template<typename T, size_t N>
struct tuple_size<array<T, N> > : public integral_constant<size_t, N> {};


// Relational operators

template<typename T, size_t N>
bool operator== (const array<T, N>& lhs, const array<T, N>& rhs);

template<typename T, size_t N>
bool operator< (const array<T, N>& lhs, const array<T, N>& rhs);

template<typename T, size_t N>
bool operator!= (const array<T, N>& lhs, const array<T, N>& rhs);

template<typename T, size_t N>
bool operator<= (const array<T, N>& lhs, const array<T, N>& rhs);

template<typename T, size_t N>
bool operator> (const array<T, N>& lhs, const array<T, N>& rhs);

template<typename T, size_t N>
bool operator>= (const array<T, N>& lhs, const array<T, N>& rhs);


// Tuple-style get

template<size_t I, typename T, size_t N>
constexpr T& get(array<T, N>& arr) noexcept;

template<size_t I, typename T, size_t N>
constexpr T& get(array<T, N>&& arr) noexcept;

template<size_t I, typename T, size_t N>
constexpr const T& get(const array<T, N>& arr) noexcept;


// Template member function implementations

// Iterators

template<typename T, size_t N>
constexpr T* array<T, N>::begin() noexcept { return arr; }

template<typename T, size_t N>
constexpr const T* array<T, N>::begin() const noexcept { return arr; }

template<typename T, size_t N>
constexpr T* array<T, N>::end() noexcept { return arr+N; }

template<typename T, size_t N>
constexpr const T* array<T, N>::end() const noexcept { return arr+N; }

template<typename T, size_t N>
constexpr const T* array<T, N>::cbegin() const noexcept { return arr; }

template<typename T, size_t N>
constexpr const T* array<T, N>::cend() const noexcept { return arr+N; }

template<typename T, size_t N>
constexpr reverse_iterator<T*> array<T, N>::rbegin() noexcept { return hsl::reverse_iterator<T*>(end()); }

template<typename T, size_t N>
constexpr reverse_iterator<const T*> array<T, N>::rbegin() const noexcept
{
    return hsl::reverse_iterator<const T*>(end());
}

template<typename T, size_t N>
constexpr reverse_iterator<T*> array<T, N>::rend() noexcept { return hsl::reverse_iterator<T*>(begin()); }

template<typename T, size_t N>
constexpr reverse_iterator<const T*> array<T, N>::rend() const noexcept
{
    return hsl::reverse_iterator<const T*>(begin());
}

template<typename T, size_t N>
constexpr reverse_iterator<const T*> array<T, N>::crbegin() const noexcept
{
    return hsl::reverse_iterator<const T*>(cend());
}

template<typename T, size_t N>
constexpr reverse_iterator<const T*> array<T, N>::crend() const noexcept
{
    return hsl::reverse_iterator<const T*>(cbegin());
}


// Capacity

template<typename T, size_t N>
constexpr size_t array<T, N>::size() const noexcept { return N; }

template<typename T, size_t N>
constexpr size_t array<T, N>::max_size() const noexcept { return N; }

template<typename T, size_t N>
constexpr bool array<T, N>::empty() const noexcept { return !N; }


// Element access

template<typename T, size_t N>
constexpr T& array<T, N>::operator[] (size_t n) { return arr[n]; }

template<typename T, size_t N>
constexpr const T& array<T, N>::operator[] (size_t n) const { return arr[n]; }

template<typename T, size_t N>
constexpr T& array<T, N>::at(size_t n)
{
    if (n >= N) throw out_of_range("hsl::array::at");
    return arr[n];
}

template<typename T, size_t N>
constexpr const T& array<T, N>::at(size_t n) const
{
    if (n >= N) throw out_of_range("hsl::array::at");
    return arr[n];
}

template<typename T, size_t N>
constexpr T& array<T, N>::front() { return arr[0]; }

template<typename T, size_t N>
constexpr const T& array<T, N>::front() const { return arr[0]; }

template<typename T, size_t N>
constexpr T& array<T, N>::back() { return arr[N-1]; }

template<typename T, size_t N>
constexpr const T& array<T, N>::back() const { return arr[N-1]; }

template<typename T, size_t N>
constexpr T* array<T, N>::data() noexcept { return arr; }

template<typename T, size_t N>
constexpr const T* array<T, N>::data() const noexcept { return arr; }


// Modifiers

template<typename T, size_t N>
void array<T, N>::fill (const T& val) { for (auto& x : arr) x = val; }

template<typename T, size_t N>
void array<T, N>::swap(array<T, N>& other) noexcept(is_nothrow_swappable<T>::value)
{
    for (auto it1 = begin(), it2 = other.begin(); it1 != end(); ++it1, ++it2)
    {
        hsl::swap(*it1, *it2);
    }
}


// Template non-member function implementations

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
