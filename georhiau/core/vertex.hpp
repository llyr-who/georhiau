#pragma once
#include <array>
#include <cmath>
#include <iostream>

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
        return vertex{m_c[0] - r.m_c[0], m_c[1] - r.m_c[1]};
    }

    const T& operator[](const std::size_t& i) const { return m_c[i]; }

private:
    std::array<T, D> m_c;
};

template <typename T, std::size_t D>
inline T norm(const vertex<T, D>& p) {
    return std::sqrt(p[0] * p[0] + p[1] * p[1]);
}

template <typename T, std::size_t D>
inline typename vertex<T, D>::orientation classify(const vertex<T, D>& p0,
                                                   const vertex<T, D>& p1,
                                                   const vertex<T, D>& p2) {
    auto a = p1 - p0;
    auto b = p2 - p0;

    // z component of cross product.
    T c_p_z = a[0] * b[1] - b[0] * a[1];
    // The sign will indicate whether the point p2
    // is to the right or the left of the line
    // segment defined by p0 and p1.
    if (c_p_z > 0.0) return vertex<T, D>::orientation::Left;
    if (c_p_z < 0.0) return vertex<T, D>::orientation::Right;
    // If we have not returned yet then
    // a and b define colinear, line segments.

    // In this case...
    // If the components of a and b have different signs
    // then p2 is behind the line segment p0,p1.
    if ((a[0] * b[0] < 0.0) || (a[1] * b[1] < 0.0))
        return vertex<T, D>::orientation::Behind;
    // If the length of b is greater than a
    if (norm(a) < norm(b)) return vertex<T, D>::orientation::Beyond;
    if (p0 == p2) return vertex<T, D>::orientation::Origin;
    if (p1 == p2) return vertex<T, D>::orientation::Destination;
    return vertex<T, D>::orientation::Between;
}

}  // namespace core
}  // namespace georhiau

