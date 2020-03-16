#include <set>

#include "core/vertex.hpp"

namespace georhiau {
namespace core {
template <typename T, std::size_t N>
class polygon {
public:
    using vertex = georhiau::core::vertex<T, 2>;
    using vertices = std::set<vertex>;

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

    vertices dump_verts() { return m_vs; }

private:
    vertices m_vs;
};
}  // namespace core
}  // namespace georhiau
