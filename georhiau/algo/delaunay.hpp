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
class frontier {
private:
    std::set<edge<T>> m_fron;
    std::set<edge<T>> m_dead;

public:
    frontier() {}

    void insert(const edge<T>& e) { m_fron.insert(e); }

    bool update(const vertex<T>& a, const vertex<T>& b) {
        auto e = edge<T>{a, b};
        auto e_rev = edge<T>{b, a};

        // If we find the reverse then we need to quit early...
        auto it_rev_fron = m_fron.find(e_rev);
        // as we have not yet popped it off and processed it.
        // If we continue, we are going to unnecc. add it (duplicate entries).
        if (it_rev_fron != m_fron.end()) {
            return false;
        }

        // If we have processed the edge then we need to check the graveyard.
        // If it has been processed then it is in the graveyard.
        // Remember an edge is considered dead if both it (e) and
        // its reverse (e_rev) are in the graveyard.
        // Since we place both in the graveyard we only need to search for
        // the edge XOR its reverse.
        auto it_rev_dead = m_dead.find(e_rev);
        if (it_rev_dead != m_dead.end()) {
            return false;
        }

        // Now we look for the edge.
        auto it_fron = m_fron.find(e);
        if (it_fron == m_fron.end()) {
            // If we have not found the edge then it is to become live.
            // That is, we add it's reverse. The reason for this is that
            // immediately after the "update" call we add the triangle
            // which has e as a face.
            m_fron.insert(e_rev);
            return true;
        } else {
            // If we found the edge then we need to remove it from the
            // frontier as it has already been dealt with and we should
            // NOT add a triangle that has e as a face.
            m_dead.insert(e);
            m_dead.insert(e_rev);
            m_fron.erase(it_fron);
            return false;
        }
    }

    auto pop_min() {
        auto min = *m_fron.begin();
        auto min_rot = edge<T>(min.dest(), min.orig());
        m_dead.insert(min);
        m_dead.insert(min_rot);
        m_fron.erase(m_fron.begin());
        return min;
    }

    bool empty() const { return m_fron.empty(); }

    void print() const {
        std::cout << "m_fron" << std::endl;
        for (const auto& e : m_fron) {
            georhiau::core::print(e);
        }
        std::cout << "m_dead" << std::endl;
        for (const auto& e : m_dead) {
            georhiau::core::print(e);
        }
    }
};

template <typename T>
auto delaunay(std::vector<vertex<T>>& cloud) {
    std::list<triangle<T>> triangles;
    frontier<T> f;
    auto e = georhiau::algo::first_hull_edge<T>(cloud);
    f.insert(e);
    while (!f.empty()) {
        auto e = f.pop_min();
        auto p = mate2(e, cloud);
        if (p == cloud.end()) continue;
        f.update(*p, e.orig());
        f.update(e.dest(), *p);
        triangles.push_back(triangle<T>{e.orig_ref(), e.dest_ref(), *p});
    }
    return triangles;
}

}  // namespace algo
}  // namespace georhiau

