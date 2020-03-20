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
void print_frontier(const std::set<edge<T>>& frontier) {
    std::cout << "state of front" << std::endl;
    for (const auto& e : frontier) {
        georhiau::core::print(e);
    }
}

template <typename T>
void update_frontier(std::set<edge<T>>& frontier, const vertex<T>& a,
                     const vertex<T>& b) {
    edge<T> e(a, b);
    // std::cout << "edge we are looking for" << std::endl;
    // georhiau::core::print(e);
    std::cout << " we are looking for " << std::endl;
    georhiau::core::print(e);
    std::cout << "what is in there" << std::endl;
    print_frontier(frontier);
    auto it = frontier.find(e);
    if (it == frontier.end()) {
        auto flip = georhiau::core::flip(e);
        frontier.insert(flip);
    } else {
        //    std::cout << "got it" << std::endl;
        frontier.erase(it);
    }
}

template <typename T>
auto delaunay(std::vector<vertex<T>>& cloud) {
    std::list<triangle<T>> triangles;
    std::set<edge<T>> frontier;
    auto e = georhiau::algo::first_hull_edge<T>(cloud);
    frontier.insert(e);
    std::size_t I = 0;
    while (!frontier.empty()) {
        auto e = *frontier.begin();
        //        print_frontier(frontier);
        frontier.erase(frontier.begin());  // remove min.
        auto p = mate2(e, cloud);
        if (p == cloud.end()) continue;
        update_frontier(frontier, *p, e.orig());
        update_frontier(frontier, e.dest(), *p);
        triangles.push_back(triangle<T>{e.orig_ref(), e.dest_ref(), *p});
        auto t = triangle<T>{e.orig_ref(), e.dest_ref(), *p};
        /*
        georhiau::core::print(t);
        std::cout << std::endl;
        std::cout << I++ << std::endl;
         */
    }
    return triangles;
}

}  // namespace algo
}  // namespace georhiau

