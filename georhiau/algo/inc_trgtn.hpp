#pragma once

#include <algorithm>
#include <iterator>
#include <list>
#include <set>
#include <stdexcept>

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
auto visible(const vertex<T>& v, const edge<T>& e) {
    // is the vertex to the right of the
    // line defined by e
    if (georhiau::core::classify(e.orig(), e.dest(), v) ==
        vertex<T>::orientation::Right) {
        return true;
    }
    return false;
}

template <typename T>
auto inc_trgtn(std::vector<vertex<T>> cloud) {
    std::list<triangle<T>> tris;

    if (cloud.size() < 3) {
        throw std::runtime_error("Less than 3 vertices.");
    }
    std::sort(cloud.rbegin(), cloud.rend());

    auto it = cloud.end();
    auto t = triangle<T>{*(it - 1), *(it - 2), *(it - 3)};
    tris.push_back(t);

    edge<T> e1(*(it - 3), *(it - 2));
    edge<T> e2(*(it - 2), *(it - 1));
    edge<T> e3(*(it - 1), *(it - 3));

    // we add the edges such that "right" of the edge
    // is inside the triangle TO BE FOUND (if there is one).
    // For example, to the right of e1 there does not exist
    // a triangle currently in tris that has it.

    std::list<edge<T>> front = {e1, e2, e3};

    cloud.erase(it - 3, it - 1);

    while (!cloud.empty()) {
        // obtain next vertex
        const auto v = cloud.back();
        // remove it
        cloud.pop_back();

        std::list<edge<T>> new_front_edges;

        while (!front.empty()) {
            // obtain and remove edge from front
            auto e = front.back();
            front.pop_back();

            // can v see e?
            if (visible(v, e)) {
                // form a triangle
                auto t = triangle<T>{e.orig_ref(), e.dest_ref(), v};
                // insert triangle
                tris.push_back(t);
                // add more edges
                auto e1 = edge<T>(e.orig(), v);
                auto e2 = edge<T>(v, e.dest());
                front.push_back(e1);
                front.push_back(e2);
            } else {
                // try again with another vertex.
                new_front_edges.push_back(e);
            }


            // DEBUG
            std::cout << "old_front" << std::endl;
            for(const auto& e: front) {
                georhiau::core::print(e);
            }
            std::cout << "new_front" << std::endl;
            for(const auto& e: new_front_edges) {
                georhiau::core::print(e);
            }
            std::cout << "--------" << std::endl;
        }

        // put all new edges to deal with back in frontier
        std::swap(front, new_front_edges);
    }

    return tris;
}

}  // namespace algo
}  // namespace georhiau

