#pragma once

#include <list>
#include <set>

#include "algo/giftwrap.hpp"
#include "algo/mate.hpp"
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
void update_frontier(std::set<edge<T>>& frontier, const vertex<T>& a,
                     const vertex<T>& b) {
    edge<T> e(a, b);
    auto it = frontier.find(e);
    if (it == frontier.end()) {
        std::cout << "going in" << std::endl;
        georhiau::core::print(e);
        auto flip = georhiau::core::flip(e);
        std::cout << "flipped" << std::endl;
        georhiau::core::print(flip);
        frontier.insert(flip);
    } else {
        frontier.erase(it);
    }
}

template <typename T>
auto delaunay(std::vector<vertex<T>>& cloud) {
    std::list<triangle<T>> triangles;
    std::set<edge<T>> frontier;
    auto e = georhiau::algo::first_hull_edge<T>(cloud);
    frontier.insert(e);
    while (!frontier.empty()) {
        auto e = *frontier.begin();
        georhiau::core::print(e);
        frontier.erase(frontier.begin());  // remove min.
        auto p = mate(e, cloud);
        if (p == cloud.end()) continue;
        update_frontier(frontier, *p, e.orig());
        update_frontier(frontier, e.dest(), *p);
        //triangle<T> t(e.orig_ref(), e.dest_ref(), *p);
    }
    return triangles;
}

}  // namespace algo
}  // namespace georhiau

