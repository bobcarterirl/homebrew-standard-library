#pragma once

#include <type_traits>

namespace hsl
{

template<typename T>
using is_nothrow_swappable = std::is_nothrow_swappable<T>;


template<typename T, T v>
struct integral_constant
{
    static constexpr T value = v;

    using value_type = T;
    using type = integral_constant;

    constexpr operator T() const noexcept;
    constexpr T operator() () const noexcept;
};

using true_type = std::integral_constant<bool, true>;
using false_type = std::integral_constant<bool, false>;


// Template member function implementations

template<typename T, T v>
constexpr integral_constant<T, v>::operator T() const noexcept { return v; }

template<typename T, T v>
constexpr T integral_constant<T, v>::operator() () const noexcept { return v; }

}
