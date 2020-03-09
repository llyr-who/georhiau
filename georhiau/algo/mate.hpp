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

// mate version 1 (my version)
// if the return value is cloud.end() then we have failed
template <typename T>
auto mate(const edge<T>& e, const std::vector<vertex<T>>& cloud) {
    auto best_p = cloud.end();
    T t, best_t = std::numeric_limits<T>::max();
    auto e_rot = georhiau::core::rotate(e);
    for (auto pnt = cloud.begin(); pnt != cloud.end(); ++pnt) {
        // obtain midpoint
        auto m = e.midpoint();
        // change of origin
        auto coo = *pnt - m;
        auto bisec_vec = e.orig() - m;
        // project coo (change of origin) onto e_rot(ten) (90's punk rock apple
        // product)
        t = coo * bisec_vec;
        if (t <= 0) continue;  // not rhs
        if (t < best_t) {
            best_t = t;
            best_p = pnt;
        }
    }
    return best_p;
}

// mate version 2 (temp for benchmarking and testing)
// "I stole this from a book" version
template <typename T>
auto mate2(const edge<T>& e, const std::vector<vertex<T>>& cloud) {
    auto best_p = cloud.end();
    T t, best_t = std::numeric_limits<T>::max();
    auto e_rot = georhiau::core::rotate(e);
    for (auto pnt = cloud.begin(); pnt != cloud.end(); ++pnt) {
        // obtain midpoint
        auto m = e.midpoint();
        // change of origin
        auto coo = *pnt - m;
        auto bisec_vec = e.orig() - m;
        // project coo (change of origin) onto e_rot(ten) (90's punk rock apple
        // product)
        t = coo * bisec_vec;
        if (t <= 0) continue;  // not rhs
        if (t < best_t) {
            best_t = t;
            best_p = pnt;
        }
    }
    return best_p;
}

}  // namespace algo
}  // namespace georhiau

