#pragma once

#include <cstddef>

namespace std
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
        // TODO reverse_iterator, const_""
        using size_type = size_t;
        using difference_type = ptrdiff_t;


        // Iterators
        T* begin() noexcept { return arr; }
        const T* begin() const noexcept { return arr; }

        T* end() noexcept { return arr+N; }
        const T* end() const noexcept { return arr+N; }

        const T* cbegin() const noexcept { return arr; }
        const T* cend() const noexcept { return arr+N; }


        // Capacity
        constexpr size_t size() const noexcept { return N; }
        constexpr size_t max_size() const noexcept { return N; }
        constexpr bool empty() const noexcept { return !N; }


        // Element access
        T& operator[] (size_t n) { return arr[n]; }
        const T& operator[] (size_t n) const { return arr[n]; }

        // TODO throw std::out_of_range if n >= N
        T& at(size_t n) { return arr[n]; }
        const T& at(size_t n) const { return arr[n]; }

        T& front() { return arr[0]; }
        const T& front() const { return arr[0]; }

        T& back() { return arr[N-1]; }
        const T& back() const { return arr[N-1]; }

        T* data() noexcept { return arr; }
        const T* data() const noexcept { return arr; }


        // Modifiers
        void fill (const T& val) { for (auto& x : arr) x = val; }
        // TODO swap

    private:
        T arr[N];
    };


    // TODO get, tuple_element, tuple_size

    // Relational operators
    // TODO use std::equal
    template<typename T, size_t N>
    bool operator== (const array<T, N>& lhs, const array<T, N>& rhs)
    {
        for (auto lit = lhs.begin(), rit = rhs.begin(); lit != lhs.end(); lit++, rit++)
        {
            if (!(*lit == *rit)) return false;
        }

        return true;
    }

    // TODO use std::lexographical_compare
    template<typename T, size_t N>
    bool operator< (const array<T, N>& lhs, const array<T, N>& rhs)
    {
        for (auto lit = lhs.begin(), rit = rhs.begin(); lit != lhs.end(); lit++, rit++)
        {
            if (*lit < *rit) return true;
            else if (*rit < *lit) return false;
        }

        return false;
    }

    template<typename T, size_t N>
    bool operator!= (const array<T, N>& lhs, const array<T, N>& rhs)
    {
        return !(lhs == rhs);
    }

    template<typename T, size_t N>
    bool operator<= (const array<T, N>& lhs, const array<T, N>& rhs)
    {
        return !(rhs < lhs);
    }

    template<typename T, size_t N>
    bool operator> (const array<T, N>& lhs, const array<T, N>& rhs)
    {
        return rhs < lhs;
    }

    template<typename T, size_t N>
    bool operator>= (const array<T, N>& lhs, const array<T, N>& rhs)
    {
        return !(lhs < rhs);
    }
}
