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

    void insert(const edge<T>& e) {
        m_fron.insert(e);
    }
    
    void update(const vertex<T>& a, const vertex<T>& b) {
        auto e = edge<T>{a, b};
        auto e_rev = edge<T>{b, a};
        
        // If we find the reverse then we need to quit early...
        auto it_rev_fron = m_fron.find(e_rev);
        // as we have not yet popped it off and dealt with it.
        if(it_rev_fron != m_fron.end()) {
            return;
        }
        
        // If is has been dealt with (e_rev) and
        // we attempt to add it again, we need to check this.
        // i.e does this edge exist in the graveyard?
        auto it_rev_dead = m_dead.find(e_rev);
        if(it_rev_dead != m_dead.end()) {
            return;
        }
        
        // now we look for the edge.
        auto it_fron = m_fron.find(e);
        if (it_fron == m_fron.end()) {
            m_fron.insert(e_rev);
        } else {
            m_dead.insert(*it_fron);
            m_fron.erase(it_fron);
        }
    }

    auto pop_min() {
        auto min = *m_fron.begin();
        m_dead.insert(min);
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

