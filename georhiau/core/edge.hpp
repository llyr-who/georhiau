#include "georhiau/core/point.hpp"

namespace georhiau {
namespace core {
template <typename T, std::size_t D>
class edge {
public:
    explicit edge(point<T, D> o, point<T, D> d) : m_orig(o), m_dest(d) {
        std::static_assert(D == 2, "Only implemented for D == 2.");
    }

private:
    point<T, D> m_orig;
    point<T, D> m_dest;
};
}  // namespace core
}  // namespace georhiau

