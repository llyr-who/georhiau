#pragma once
#include <algorithm>
#include <limits>
#include <memory>
#include <vector>

#include "core/edge.hpp"
#include "core/vertex.hpp"

namespace georhiau {

//! This calculates the closest point to an edge.
//! The logic uses the fact that there are an
//! infnite number of circles that pass through
//! two points. The centres of these circles form
//! the perpendicular bisector. By considering
//! other points in the cloud (one at a time),
//! we wish to find the circle that passes through
//! the end points of the edge and the point
//! under consideration such that the radius
//! is minimised.
template <typename T>
auto mate(const edge<T, 2>& e, const std::vector<vertex<T, 2>>& cloud) {
    auto best_p = cloud.end();
    T t, best_t = std::numeric_limits<T>::max();
    auto e_rot = georhiau::rotate(e);
    for (auto pnt = cloud.begin(); pnt != cloud.end(); ++pnt) {
        // Escape early if we are not on the right.
        if (georhiau::classify(e.orig(), e.dest(), *pnt) !=
            vertex<T, 2>::orientation::Right) {
            continue;
        }
        edge<T, 2> g = rotate(edge<T, 2>{e.dest(), *pnt});

        // this gives us the intersection parameter t
        // that specifies the centre of the circle
        // along e_rot.
        auto [type, t] = georhiau::intersect(e_rot, g);

        // We don't want a mate that is parallel or colinear.
        if (type == edge<T, 2>::intersection::Parallel ||
            type == edge<T, 2>::intersection::Colinear) {
            continue;
        }
        //
        if (t < best_t) {
            best_p = pnt;
            best_t = t;
        }
    }
    return best_p;
}

}  // namespace georhiau

