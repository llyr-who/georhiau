#pragma once
#include "core/polygon.hpp"

namespace georhiau {
template <typename T>
using triangle = polygon<T, 3>;

template <typename T>
T area(const triangle<T>& t) {
    auto a = t[0], b = t[1], c = t[2];
    auto ab = b - a;
    auto ac = c - a;
    return 0.5 * std::abs(georhiau::cross(ab, ac));
}

}  // namespace georhiau

