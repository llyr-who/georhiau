#include <array>
#include <cmath>

//! point class.
//! T is the type.
//! D is the dimension of the space.

namespace georhiau {
namespace core {
template <typename T, std::size_t D>
class point {
public:
    template <typename... Ts,
              typename std::enable_if<
                  std::conjunction<std::is_same<T, Ts>...>::value &&
                      (sizeof...(Ts) == D),
                  int>::type = 0>
    constexpr point(Ts&&... elements) noexcept {
        m_c = std::array<T, D>{std::forward<Ts>(elements)...};
        //! We could end up only having D = 2,3.
        //! As these are the most commonly used dims.
        static_assert(D == 2, "Only implemented for D == 2.");
    }

    bool operator<(const point<T, D>& r) {
        return m_c[0] < r.m_c[0] ||
               (std::fabs(m_c[0] - r.m_c[0]) < 1e-6 && m_c[1] < r.m_c[1]);
    }

private:
    std::array<T, D> m_c;
};
}  // namespace core
}  // namespace georhiau

