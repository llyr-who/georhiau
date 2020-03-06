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

private:
    vertex<T, D> m_orig;
    vertex<T, D> m_dest;
};

template<typename T, std::size_t D>
inline void print(const edge<T,D>& e) {
    std::cout << '\n';
    print(e.orig());
    print(e.dest());
    std::cout << std::endl;
}

}  // namespace core
}  // namespace georhiau

