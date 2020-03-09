#pragma once
#include <algorithm>
#include <limits>
#include <memory>
#include <optional>
#include <vector>

#include "core/edge.hpp"
#include "core/vertex.hpp"

namespace georhiau {
namespace algo {

// rsi prevention
template <typename T>
using edge = georhiau::core::edge<double, 2>;

template <typename T>
using vertex = georhiau::core::vertex<double, 2>;

template <typename T>
std::optional<point> mate(const edge& e, const std::vector<vertex>& cloud,
                          const int n) {
    std::unique_ptr<point> best_p;
    T t, best_t = std::numeric_limits<T>::max();
    auto e_rot = georhiau::core::rotate(e);
    for (const auto& pnt : cloud) {
        // we only want to deal with points on the right
        if (georhiau::core::classify(e.orig(), e.dest(), pnt) !=
            vertex::core::Right) {
            continue;
        }
    }
}

}  // namespace algo
}  // namespace georhiau

