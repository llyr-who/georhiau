#pragma once
#include "core/vertex.hpp"

namespace georhiau {

template <typename T, std::size_t D>
class edge {
public:
    enum class intersection {
        Colinear,
        Parallel,
        Skew,
        SkewCross,
        SkewNoCross
    };

    explicit edge(vertex<T, D> o, vertex<T, D> d) : m_orig(o), m_dest(d) {
        static_assert(D == 2, "Only implemented for D == 2.");
    }

    bool operator==(const edge<T, D>& e) const {
        return ((m_orig == e.m_orig) && (m_dest == e.m_dest));
    }

    bool operator<(const edge<T, D>& e) const {
        if ((m_orig < e.m_orig) ||
            ((m_orig == e.m_orig) && (m_dest < e.m_dest)))
            return true;
        return false;
    }

    const vertex<T, D>& orig_ref() const { return m_orig; }
    const vertex<T, D>& dest_ref() const { return m_dest; }
    vertex<T, D> orig() const { return m_orig; }
    vertex<T, D> dest() const { return m_dest; }
    vertex<T, D> midpoint() const { return 0.5 * (m_orig + m_dest); }

private:
    vertex<T, D> m_orig;
    vertex<T, D> m_dest;
};

template <typename T, std::size_t D>
using intersect_type_param = std::pair<typename edge<T, D>::intersection, T>;

//
// returns intersection type and parameter.
//
template <typename T, std::size_t D>
inline intersect_type_param<T, D> intersect(const edge<T, D>& e1,
                                            const edge<T, D>& e2) {
    auto a = e1.orig();
    auto b = e1.dest();
    auto c = e2.orig();
    auto d = e2.dest();
    auto cd_data = (d - c).data();
    vertex<T, D> n = {1.0 * cd_data[1], -1.0 * cd_data[0]};
    auto proj = n * (b - a);
    // If proj is zero then (a,b) and (c,d) are parallel. (or even colinear)
    // Note the magic number here.
    if (std::abs(proj) <= 10e-15) {
        auto point_class = classify(e2.orig(), e2.dest(), e1.orig());
        if ((point_class == vertex<T, D>::orientation::Left) ||
            (point_class == vertex<T, D>::orientation::Right)) {
            return std::make_pair(edge<T, D>::intersection::Parallel, T());
        } else {
            return std::make_pair(edge<T, D>::intersection::Colinear, T());
        }
    }
    return std::make_pair(edge<T, D>::intersection::Skew, (n * (c - a)) / proj);
}

template <typename T, std::size_t D>
inline T length(const edge<T, D>& e) {
    auto diff = e.dest() - e.orig();
    return georhiau::norm(diff);
}

//! rotates clockwise!
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
inline edge<T, D> flip(const edge<T, D>& e) {
    return edge<T, D>(e.dest(), e.orig());
}

template <typename T, std::size_t D>
inline void print(const edge<T, D>& e) {
    std::cout << '\n';
    print(e.orig());
    print(e.dest());
    std::cout << std::endl;
}

}  // namespace georhiau

