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

private:
    vertex<T, D> m_orig;
    vertex<T, D> m_dest;
};
}  // namespace core
}  // namespace georhiau

