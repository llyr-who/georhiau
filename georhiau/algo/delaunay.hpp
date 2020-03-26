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

    void kill_edge(const typename std::set<edge<T>>::iterator& it) {
        m_fron.erase(it);
        m_dead.insert(*it);
    }

public:
    frontier() {}

    void insert(const edge<T>& e) { m_fron.insert(e); }

    bool update(const vertex<T>& a, const vertex<T>& b) {
        auto e = edge<T>{a, b};
        auto e_rev = edge<T>{b, a};

        auto it_rev_dead = m_dead.find(e_rev);
        auto it_dead = m_dead.find(e);
        if (it_rev_dead != m_dead.end() || it_dead != m_dead.end()) {
            return false;
        }

        auto it_rev_fron = m_fron.find(e_rev);
        if (it_rev_fron != m_fron.end()) {
            return false;
        }

        auto it_fron = m_fron.find(e);
        if (it_fron == m_fron.end()) {
            m_fron.insert(e_rev);
            return true;
        }

        kill_edge(it_fron);
        return false;
    }

    auto pop_min() {
        auto min = *m_fron.begin();
        kill_edge(m_fron.begin());
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
    int I = 0;
    while (!f.empty()) {
        auto e = f.pop_min();
        auto p = mate2(e, cloud);
        if (p == cloud.end()) continue;
        bool face1 = f.update(*p, e.orig());
        bool face2 = f.update(e.dest(), *p);
        if (!face1 && !face2) continue;
        triangles.push_back(triangle<T>{e.orig_ref(), e.dest_ref(), *p});
    }
    return triangles;
}

}  // namespace algo
}  // namespace georhiau

