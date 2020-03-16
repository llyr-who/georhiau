#pragma once
#include <algorithm>
#include <vector>

#include "core/edge.hpp"
#include "core/vertex.hpp"

namespace georhiau {
namespace algo {

template <typename T>
using edge = georhiau::core::edge<T, 2>;

template <typename T>
using vertex = georhiau::core::vertex<T, 2>;

template <typename T>
auto smallest_vertex(std::vector<vertex<T>>& cloud) {
    if (cloud.empty()) throw std::runtime_error("empty");
    return std::min_element(cloud.begin(), cloud.end());
}

template <typename T>
auto first_hull_edge(std::vector<vertex<T>>& cloud) {
    auto smallest = smallest_vertex<T>(cloud);
    std::iter_swap(smallest, cloud.begin());

    std::size_t m = 1, i = 2;
    for (; i < cloud.size(); ++i) {
        auto orientation = core::classify(cloud.front(), cloud[m], cloud[i]);

        if ((orientation == vertex<T>::orientation::Left) ||
            (orientation == vertex<T>::orientation::Between)) {
            m = i;
        }
    }

    return edge<T>{cloud.front(), cloud[m]};
}

}  // namespace algo
}  // namespace georhiau

