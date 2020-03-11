#include "core/vertex.hpp"

namespace georhiau {
namespace core {
template <typename T, std::size_t N>
class polygon {
public:
    using vertex = georhiau::core::vertex<T, 2>;
    using vertices = std::array<vertex, N>;

    template <typename... Ts,
              typename std::enable_if<
                  std::conjunction<std::is_same<vertex&, Ts>...>::value &&
                      (sizeof...(Ts) == N),
                  int>::type = 0>
    constexpr polygon(Ts&&... verts) {
        m_vs = std::array<vertex, N>{std::forward<Ts>(verts)...};
    }

    vertices dump_verts() { return m_vs; }

private:
    vertices m_vs;
};
}  // namespace core
}  // namespace georhiau
