#pragma once
#include "core/vertex.hpp"

namespace georhiau {
namespace core {
template <typename T, std::size_t D>
class edge {
public:
    explicit edge(vertex<T, D> o, vertex<T, D> d) : m_orig(o), m_dest(d) {
        static_assert(D == 2, "Only implemented for D == 2.");
    }

    bool operator==(const edge<T, D>& e) const {
        return ((m_orig == e.m_orig) && (m_dest == e.m_dest));
    }

    vertex<T, D> orig() const { return m_orig; }
    vertex<T, D> dest() const { return m_dest; }
    vertex<T, D> midpoint() const { return 0.5 * (m_orig + m_dest); }

private:
    vertex<T, D> m_orig;
    vertex<T, D> m_dest;
};

template <typename T, std::size_t D>
inline edge<T, D> rotate(const edge<T, D>& e) {
    auto orig = e.orig();
    auto dest = e.dest();

    // midpoint
    auto m = e.midpoint();
    auto dir = dest - orig;
    vertex<T, D> normal_dir = {1.0 * dir.data()[1], -1.0 * dir.data()[0]};
    // note that cross(dir,normal_dir) > 0
    return edge<T, D>(m - 0.5 * normal_dir, m + 0.5 * normal_dir);
}

template <typename T, std::size_t D>
inline void print(const edge<T, D>& e) {
    std::cout << '\n';
    print(e.orig());
    print(e.dest());
    std::cout << std::endl;
}

}  // namespace core
}  // namespace georhiau

