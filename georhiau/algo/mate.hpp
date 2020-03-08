#pragma once
#include <algorithm>
#include <vector>

#include "core/edge.hpp"
#include "core/vertex.hpp"

namespace georhiau {
namespace algo {

// rsi prevention
template <typename T>
using edge = georhiau::core::edge<double, 2>;

template <typename T>
using vertex = georhiau::core::vertex<double, 2>;




}  // namespace algo
}  // namespace georhiau

