#pragma once
#include <algorithm>
#include <list>
#include <vector>

#include "core/edge.hpp"
#include "core/vertex.hpp"

namespace georhiau {

template <typename T>
using point_cloud = std::vector<vertex<T, 2>>;

// Given a point and a point cloud, this routine returns
// an edge. The origin being p0 and the destination being the
// vertex that makes the edge the left most.
// The complexity is linear
template <typename T>
auto left_most_edge(const vertex<T, 2>& p0, const point_cloud<T>& cloud) {
    std::size_t m = 0, i = 1;
    for (; i < cloud.size(); ++i) {
        if (cloud[m] == p0) {
            ++m;
            continue;
        }
        auto orientation = classify(p0, cloud[m], cloud[i]);

        if ((orientation == vertex<T, 2>::orientation::Left) ||
            (orientation == vertex<T, 2>::orientation::Between)) {
            m = i;
        }
    }
    return edge<T, 2>{p0, cloud[m]};
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

template <typename T>
auto giftwrap(const point_cloud<T>& c) {
    // assert that we must have 2 verts
    if (c.size() < 2) {
        // we want the program to terminate.
        throw std::runtime_error("point cloud with size 2");
    }
    // obtain first hull edge
    auto e0 = first_hull_edge(c);
    // obtain next edge.
    auto e = left_most_edge(e0.dest(), c);

    std::list<edge<T, 2>> convex_hull = {e0};
    while (e.dest() != e0.dest()) {
        convex_hull.push_back(e);
        e = left_most_edge(e.dest(), c);
    }
    return convex_hull;
}

}  // namespace georhiau

