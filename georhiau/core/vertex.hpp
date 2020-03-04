#include <array>
#include <cmath>

//! vertex class.
//! T is the type.
//! D is the dimension of the space.

namespace georhiau {
namespace core {
template <typename T, std::size_t D>
class vertex {
public:
    enum class orientation {
        Left,
        Right,
        Beyond,
        Behind,
        Between,
        Origin,
        Destination
    };

    T tol = std::numeric_limits<T>::min();

    vertex() : m_c({}) {}

    template <typename... Ts,
              typename std::enable_if<
                  std::conjunction<std::is_same<T, Ts>...>::value &&
                      (sizeof...(Ts) == D),
                  int>::type = 0>
    constexpr vertex(Ts&&... elements) noexcept {
        m_c = std::array<T, D>{std::forward<Ts>(elements)...};
        //! We could end up only having D = 2,3.
        //! As these are the most commonly used dims.
        static_assert(D == 2, "Only implemented for D == 2.");
    }

    bool operator<(const vertex<T, D>& r) const {
        return m_c[0] < r.m_c[0] ||
               (std::fabs(m_c[0] - r.m_c[0]) < tol && m_c[1] < r.m_c[1]);
    }

    bool operator==(const vertex<T, D>& r) const {
        return (std::fabs(m_c[0] - r.m_c[0]) < tol) &&
               (std::fabs(m_c[1] - r.m_c[1]) < tol);
    }

    vertex operator-(const vertex<T, D>& r) const {
        vertex{m_c[0] - r.m_c[0], m_c[1] - r.m_c[1]};
    }

private:
    std::array<T, D> m_c;
};

template <typename T, std::size_t D>
inline int classify(const vertex<T, D>& p0, const vertex<T, D>& p1,
                    const vertex<T, D>& p2) {
    auto a = p1 - p0;
    auto b = p2 - p0;

    // z component of cross product.
    T c_p_z = a.x * b.y - b.x * a.y;
    // The sign will indicate whether the point p2
    // is to the right or the left of the line
    // segment defined by p0 and p1.
    if (c_p_z > 0.0) return vertex<T, D>::orientation::Left;
    if (c_p_z < 0.0) return vertex<T, D>::orientation::Right;
    // If we have not returned yet then
    // a and b define colinear, line segments.
}

}  // namespace core
}  // namespace georhiau

