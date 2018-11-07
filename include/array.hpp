#pragma once

#include <cstddef>
#include "algorithm.hpp"
#include "iterator.hpp"     // hbstl::begin, hbstl::end defined here
#include "stdexcept.hpp"

namespace hbstl
{

template<typename T, std::size_t N>
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
    using reverse_iterator = reverse_iterator<T*>;
    using const_reverse_iterator = reverse_iterator<const T*>;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;


    // Iterators
    T* begin() noexcept;
    const T* begin() const noexcept;

    T* end() noexcept;
    const T* end() const noexcept;

    const T* cbegin() const noexcept;
    const T* cend() const noexcept;

    reverse_iterator<T*> rbegin() noexcept;
    reverse_iterator<const T*> rbegin() const noexcept;

    reverse_iterator<T*> rend() noexcept;
    reverse_iterator<const T*> rend() const noexcept;

    reverse_iterator<const T*> crbegin() const noexcept;
    reverse_iterator<const T*> crend() const noexcept;


    // Capacity
    constexpr std::size_t size() const noexcept;
    constexpr std::size_t max_size() const noexcept;
    constexpr bool empty() const noexcept;


    // Element access
    T& operator[] (std::size_t n);
    const T& operator[] (std::size_t n) const;

    T& at(std::size_t n);
    const T& at(std::size_t n) const;

    T& front();
    const T& front() const;

    T& back();
    const T& back() const;

    T* data() noexcept;
    const T* data() const noexcept;


    // Modifiers
    void fill (const T& val);
    // TODO swap

private:
    T arr[N];
};


// TODO get, tuple_element, tuple_size, begin, end

// Relational operators

template<typename T, std::size_t N>
bool operator== (const array<T, N>& lhs, const array<T, N>& rhs);

template<typename T, std::size_t N>
bool operator< (const array<T, N>& lhs, const array<T, N>& rhs);

template<typename T, std::size_t N>
bool operator!= (const array<T, N>& lhs, const array<T, N>& rhs);

template<typename T, std::size_t N>
bool operator<= (const array<T, N>& lhs, const array<T, N>& rhs);

template<typename T, std::size_t N>
bool operator> (const array<T, N>& lhs, const array<T, N>& rhs);

template<typename T, std::size_t N>
bool operator>= (const array<T, N>& lhs, const array<T, N>& rhs);


// Template member function implementations

// Iterators

template<typename T, std::size_t N>
T* array<T, N>::begin() noexcept { return arr; }

template<typename T, std::size_t N>
const T* array<T, N>::begin() const noexcept { return arr; }

template<typename T, std::size_t N>
T* array<T, N>::end() noexcept { return arr+N; }

template<typename T, std::size_t N>
const T* array<T, N>::end() const noexcept { return arr+N; }

template<typename T, std::size_t N>
const T* array<T, N>::cbegin() const noexcept { return arr; }

template<typename T, std::size_t N>
const T* array<T, N>::cend() const noexcept { return arr+N; }

template<typename T, std::size_t N>
reverse_iterator<T*> array<T, N>::rbegin() noexcept { return reverse_iterator<T*>(end()); }

template<typename T, std::size_t N>
reverse_iterator<const T*> array<T, N>::rbegin() const noexcept { return reverse_iterator<const T*>(end()); }

template<typename T, std::size_t N>
reverse_iterator<T*> array<T, N>::rend() noexcept { return reverse_iterator<T*>(begin()); }

template<typename T, std::size_t N>
reverse_iterator<const T*> array<T, N>::rend() const noexcept { return reverse_iterator<const T*>(begin()); }

template<typename T, std::size_t N>
reverse_iterator<const T*> array<T, N>::crbegin() const noexcept { return reverse_iterator<const T*>(cend()); }

template<typename T, std::size_t N>
reverse_iterator<const T*> array<T, N>::crend() const noexcept { return reverse_iterator<const T*>(cbegin()); }


// Capacity

template<typename T, std::size_t N>
constexpr std::size_t array<T, N>::size() const noexcept { return N; }

template<typename T, std::size_t N>
constexpr std::size_t array<T, N>::max_size() const noexcept { return N; }

template<typename T, std::size_t N>
constexpr bool array<T, N>::empty() const noexcept { return !N; }


// Element access

template<typename T, std::size_t N>
T& array<T, N>::operator[] (std::size_t n) { return arr[n]; }

template<typename T, std::size_t N>
const T& array<T, N>::operator[] (std::size_t n) const { return arr[n]; }

template<typename T, std::size_t N>
T& array<T, N>::at(std::size_t n)
{
    if (n >= N) throw out_of_range("hbstl::array::at");
    return arr[n];
}

template<typename T, std::size_t N>
const T& array<T, N>::at(std::size_t n) const
{
    if (n >= N) throw out_of_range("hbstl::array::at");
    return arr[n];
}

template<typename T, std::size_t N>
T& array<T, N>::front() { return arr[0]; }

template<typename T, std::size_t N>
const T& array<T, N>::front() const { return arr[0]; }

template<typename T, std::size_t N>
T& array<T, N>::back() { return arr[N-1]; }

template<typename T, std::size_t N>
const T& array<T, N>::back() const { return arr[N-1]; }

template<typename T, std::size_t N>
T* array<T, N>::data() noexcept { return arr; }

template<typename T, std::size_t N>
const T* array<T, N>::data() const noexcept { return arr; }


// Modifiers

template<typename T, std::size_t N>
void array<T, N>::fill (const T& val) { for (auto& x : arr) x = val; }


// Template non-member function implementations

// Relational operators

template<typename T, std::size_t N>
bool operator== (const array<T, N>& lhs, const array<T, N>& rhs)
{
    return equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<typename T, std::size_t N>
bool operator< (const array<T, N>& lhs, const array<T, N>& rhs)
{
    return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<typename T, std::size_t N>
bool operator!= (const array<T, N>& lhs, const array<T, N>& rhs)
{
    return !(lhs == rhs);
}

template<typename T, std::size_t N>
bool operator<= (const array<T, N>& lhs, const array<T, N>& rhs)
{
    return !(rhs < lhs);
}

template<typename T, std::size_t N>
bool operator> (const array<T, N>& lhs, const array<T, N>& rhs)
{
    return rhs < lhs;
}

template<typename T, std::size_t N>
bool operator>= (const array<T, N>& lhs, const array<T, N>& rhs)
{
    return !(lhs < rhs);
}

}
