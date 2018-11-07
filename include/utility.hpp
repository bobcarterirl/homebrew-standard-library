#pragma once

#include <utility>
#include "algorithm.hpp"

namespace hbstl
{

template<typename T>
void swap(T& a, T& b) { std::swap(a, b); }

}
