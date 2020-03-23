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
    // private helper class to encap. an edge
    struct f_item {
        edge<T> m_e;

        f_item(const vertex<T>& a, const vertex<T>& b) : m_e{a, b} {}
        f_item(const edge<T>& e) : m_e{e} {}
        // loosing equality on edge
        bool operator==(const f_item& fi) {
            auto e_rot = georhiau::core::rotate(fi.m_e);
            if (m_e == fi.m_e || m_e == e_rot) return true;
            return false;
        }    
    };

    std::set<edge<T>> m_fron;
    std::vector<f_item> m_dead;

public:
    frontier() {}

    void insert(const edge<T>& e) {
        m_fron.insert(e);
    }
    
    void update(const vertex<T>& a, const vertex<T>& b) {
        auto e = edge<T>{a, b};
        auto it_fron = m_fron.find(e);
        if (it_fron == m_fron.end()) {
            auto fi = f_item(e);
            auto it_dead = std::find(m_dead.begin(), m_dead.end(), fi);
            if (it_dead == m_dead.end()) {
                edge<T> re{b, a};
                m_fron.insert(re);
            }
        } else {
            m_fron.erase(it_fron);
            m_dead.push_back(*it_fron);
        }
    }

    auto pop_min() {
        auto min = *m_fron.begin();
        m_fron.erase(m_fron.begin());
        return min;
    }

    bool empty() const { return m_fron.empty(); }

    auto dump() const { return m_fron; }
};

template <typename T>
void print(const frontier<T>& f) {
    for (const auto& e : f.dump()) {
        georhiau::core::print(e);
    }
}

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

