#pragma once

#include <type_traits>

namespace hsl
{

template<typename T>
using is_nothrow_swappable = std::is_nothrow_swappable<T>;

}
