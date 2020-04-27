#pragma once 
#include <iterator>
#include <set>

#include "core/vertex.hpp"

namespace georhiau {
template <typename T, std::size_t N>
class polygon {
public:
    using vertex = georhiau::vertex<T, 2>;
    // We use a set since {v1,v2,v3} == {v3,v2,v1}
    // vectors cry about order. We could add them to a
    // vector and then sort.
    // Some bench marking would be useful.
    using vertices = std::set<vertex>;

    template <typename... Ts,
              typename std::enable_if<
                  std::conjunction<std::is_same<vertex&, Ts>...>::value &&
                      (sizeof...(Ts) == N),
                  int>::type = 0>
    polygon(Ts&&... verts) {
        m_vs = std::set<vertex>{std::forward<Ts>(verts)...};
    }

    template <typename... Ts,
              typename std::enable_if<
                  std::conjunction<std::is_same<const vertex&, Ts>...>::value &&
                      (sizeof...(Ts) == N),
                  int>::type = 0>
    polygon(Ts&&... verts) {
        m_vs = std::set<vertex>{std::forward<Ts>(verts)...};
    }

    bool operator==(const polygon<T, N>& p) const {
        if (p.m_vs == m_vs) return true;
        return false;
    }

    vertex operator[](std::size_t i) const {
        return *std::next(m_vs.begin(), i);
    }

    vertices dump_verts() const { return m_vs; }

private:
    vertices m_vs;
};

template <typename T, std::size_t N>
void print(const polygon<T, N>& p) {
    auto verts = p.dump_verts();
    for (const auto& v : verts) {
        print(v);
    }
}

}  // namespace georhiau
