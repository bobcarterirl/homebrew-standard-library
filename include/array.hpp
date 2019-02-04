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


private:
    // Simulates a zero length array, since they're non-standard
    class Empty_array
    {
    public:
        constexpr operator pointer() { return nullptr; }


        constexpr iterator begin() noexcept { return nullptr; }
        constexpr const_iterator begin() const noexcept { return nullptr; }

        constexpr iterator end() noexcept { return nullptr; }
        constexpr const_iterator end() const noexcept { return nullptr; }

        constexpr reverse_iterator rbegin() noexcept
        { return reverse_iterator(nullptr); }

        constexpr const_reverse_iterator rbegin() const noexcept
        { return const_reverse_iterator(nullptr); }

        constexpr reverse_iterator rend() noexcept
        { return reverse_iterator(nullptr); }

        constexpr const_reverse_iterator rend() const noexcept
        { return const_reverse_iterator(nullptr); }
    };


    using Array = hsl::conditional_t<N, T[N], Empty_array>;


public:
    // Must be public for aggregate initialization to work.
    // Don't access it directly; use data() method, instead.
    Array arr;


    // Iterators
    constexpr iterator begin() noexcept { return hsl::begin(arr); }
    constexpr const_iterator begin() const noexcept { return hsl::begin(arr); }

    constexpr iterator end() noexcept { return hsl::end(arr); }
    constexpr const_iterator end() const noexcept { return hsl::end(arr); }

    constexpr const_iterator cbegin() const noexcept
    { return hsl::cbegin(arr); }

    constexpr const_iterator cend() const noexcept
    { return hsl::cend(arr); }

    constexpr reverse_iterator rbegin() noexcept
    { return hsl::rbegin(arr); }

    constexpr const_reverse_iterator rbegin() const noexcept
    { return hsl::rbegin(arr); }

    constexpr reverse_iterator rend() noexcept
    { return hsl::rend(arr); }

    constexpr const_reverse_iterator rend() const noexcept
    { return hsl::rend(arr); }

    constexpr const_reverse_iterator crbegin() const noexcept
    { return hsl::crbegin(arr); }

    constexpr const_reverse_iterator crend() const noexcept
    { return hsl::crend(arr); } 


    // Capacity
    constexpr size_t size() const noexcept { return N; }
    constexpr size_t max_size() const noexcept { return N; }
    constexpr bool empty() const noexcept { return !N; }


    // Element access
    constexpr reference operator[] (size_t n) { return arr[n]; }
    constexpr const_reference operator[] (size_t n) const { return arr[n]; }

    constexpr reference at(size_t n)
    {
        if (n >= N) throw out_of_range("hsl::array::at");
        return arr[n];
    }

    constexpr const_reference at(size_t n) const
    {
        if (n >= N) throw out_of_range("hsl::array::at");
        return arr[n];
    }

    constexpr reference front() { return arr[0]; }
    constexpr const_reference front() const { return arr[0]; }

    constexpr reference back() { return arr[N - 1]; }
    constexpr const_reference back() const { return arr[N - 1]; }

    constexpr pointer data() noexcept { return arr; }
    constexpr const_pointer data() const noexcept { return arr; }


    // Operations
    void fill(const T& val) { hsl::fill(begin(), end(), val); }

    void swap(array<T, N>& other)
    noexcept(is_nothrow_swappable<T>::value)
    { hsl::swap(arr, other.arr); }
};
 

// Tuple helper class specializations

template<size_t I, typename T, size_t N>
struct tuple_element<I, array<T, N> >
{
    using type = T;
};

template<typename T, size_t N>
struct tuple_size<array<T, N> > : public integral_constant<size_t, N>
{};


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
    return lexicographical_compare(
            lhs.begin(), lhs.end(),
            rhs.begin(), rhs.end());
}

template<typename T, size_t N>
bool operator!= (const array<T, N>& lhs, const array<T, N>& rhs)
{ return !(lhs == rhs); }

template<typename T, size_t N>
bool operator<= (const array<T, N>& lhs, const array<T, N>& rhs)
{ return !(rhs < lhs); }

template<typename T, size_t N>
bool operator> (const array<T, N>& lhs, const array<T, N>& rhs)
{ return rhs < lhs; }

template<typename T, size_t N>
bool operator>= (const array<T, N>& lhs, const array<T, N>& rhs)
{ return !(lhs < rhs); }


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
void swap(array<T, N>& lhs, array<T, N>& rhs)
noexcept(noexcept(lhs.swap(rhs)))
{
    lhs.swap(rhs);
}

}
