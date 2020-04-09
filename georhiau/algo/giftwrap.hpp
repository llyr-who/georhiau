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
using point_cloud = std::vector<vertex<T>>;

template <typename T>
auto left_most_edge(const vertex<T>& p0, const point_cloud<T>& cloud) {
    std::size_t m = 0, i = 1;
    for (; i < cloud.size(); ++i) {
        if (cloud[m] == p0) {
            ++m;
            continue;
        }
        auto orientation = core::classify(p0, cloud[m], cloud[i]);

        if ((orientation == vertex<T>::orientation::Left) ||
            (orientation == vertex<T>::orientation::Between)) {
            m = i;
        }
    }
    return edge<T>{p0, cloud[m]};
}

template <typename T>
auto first_hull_edge(const point_cloud<T>& c) {
    // if cloud is empty, throw runtime error
    if (c.empty()) throw std::runtime_error("empty");
    // linear search for smallest element
    auto smallest_it = std::min_element(c.begin(), c.end());
    // return the "first" hull edge
    return left_most_edge<T>(*smallest_it, c);
}

}  // namespace algo
}  // namespace georhiau

