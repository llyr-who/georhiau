#pragma once

#include <list>
#include <set>

#include "algo/giftwrap.hpp"
#include "algo/mate.hpp"
#include "core/edge.hpp"
#include "core/triangle.hpp"
#include "core/vertex.hpp"

namespace georhiau {

template <typename T>
class frontier {
private:
    std::set<edge<T, 2>> m_fron;
    std::set<edge<T, 2>> m_dead;

    void kill_edge(const typename std::set<edge<T, 2>>::iterator& it) {
        m_fron.erase(it);
        m_dead.insert(*it);
    }

public:
    frontier() {}

    void insert(const edge<T, 2>& e) { m_fron.insert(e); }

    bool update(const vertex<T, 2>& a, const vertex<T, 2>& b) {
        auto e = edge<T, 2>{a, b};
        auto e_rev = edge<T, 2>{b, a};

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

    edge<T, 2> pop_min() {
        auto min = *m_fron.begin();
        kill_edge(m_fron.begin());
        return min;
    }

    bool empty() const { return m_fron.empty(); }

    void print() const {
        std::cout << "m_fron" << std::endl;
        for (const auto& e : m_fron) {
            georhiau::print(e);
        }
        std::cout << "m_dead" << std::endl;
        for (const auto& e : m_dead) {
            georhiau::print(e);
        }
    }
};

template <typename T>
auto delaunay(std::vector<vertex<T, 2>> cloud) {
    std::list<triangle<T>> triangles;
    frontier<T> f;
    auto e = georhiau::first_hull_edge<T>(cloud);
    f.insert(e);
    int I = 0;
    while (!f.empty()) {
        auto e = f.pop_min();
        auto p = mate(e, cloud);
        if (p == cloud.end()) continue;
        bool face1 = f.update(*p, e.orig());
        bool face2 = f.update(e.dest(), *p);
        if (!face1 && !face2) continue;
        triangles.push_back(triangle<T>(e.orig_ref(), e.dest_ref(), *p));
    }
    return triangles;
}

}  // namespace georhiau

