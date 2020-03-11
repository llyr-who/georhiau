#pragma once

#include <list>
#include <set>

#include "algo/giftwrap.hpp"
#include "core/edge.hpp"
#include "core/triangle.hpp"
#include "core/vertex.hpp"

namespace georhiau {
namespace algo {

template <typename T>
using vertex = georhiau::core::vertex<T, 2>;

template <typename T>
using edge = georhiau::core::edge<T, 2>;

template <typename T>
using triangle = georhiau::core::triangle<T>;

template <typename T>
void update_frontier(std::set<triangle<T>>& frontier, const vertex<T>& a,
                     const vertex<T>& b) {
    edge<T> e(a, b);
    auto it = frontier.find(e);
    if (it == frontier.end()) {
        auto flip = georhiau::core::flip(e);
        frontier.insert(flip);
    } else {
        frontier.erase(it);
    }
}

template <typename T>
void delaunay(std::vector<vertex<T>>& cloud) {
    vertex<T> p;
    std::list<triangle<T>> triangles;
    std::set<edge<T>> frontier;
    auto e = georhiau::algo::first_hull_edge<T>(cloud);
    frontier.insert(e);
    /*
    while(!frontier.empty()) {
    }
    */
}

}  // namespace algo
}  // namespace georhiau

