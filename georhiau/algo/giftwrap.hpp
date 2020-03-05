#pragma once
#include <algorithm>
#include <vector>

#include "core/edge.hpp"
#include "core/vertex.hpp"

namespace georhiau {
namespace algo {

template <typename T>
using edge = georhiau::core::edge<double, 2>;

template <typename T>
using vertex = georhiau::core::vertex<double, 2>;

template <typename T>
auto smallest_vertex(const std::vector<vertex<T>>& cloud) {
    return std::min_element(cloud.begin(), cloud.end());
}

template <typename T>
auto first_hull_edge(const std::vector<vertex<T>>& cloud) {

    auto smallest = smallest_vertex(cloud);
    std::iter_swap(smallest, cloud.begin());

    std::size_t m = 1, i = 2;
    for (; i < cloud.size(); ++i) {
        auto orientation =
            vertex<T>::classify(cloud.front(), cloud[m], cloud[i]);

        if ((orientation == vertex<T>::orientation::Left) ||
            (orientation == vertex<T>::orientation::Between)) {
            m = i;
        }
    }

    return edge<T>{cloud.front(), cloud[m]};
}

}  // namespace algo
}  // namespace georhiau

