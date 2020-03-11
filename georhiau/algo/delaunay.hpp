#pragma once

#include "core/edge.hpp"
#include "core/vertex.hpp"

namespace georhiau {
namespace algo {

template <typename T>
using vertex = georhiau::core::vertex<T, 2>;

template <typename T>
void delaunay(const std::vector<vertex<T>>& cloud) {}

}  // namespace algo
}  // namespace georhiau

