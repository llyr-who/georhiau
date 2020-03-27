#include "algo/ear_clip.hpp"

#include "gtest/gtest.h"

using vertex = georhiau::core::vertex<double, 2>;

template <std::size_t N>
using polygon = georhiau::core::polygon<double, N>;

TEST(ear_clip, basic) {
    const vertex a = {1.0, 1.0};
    const vertex b = {3.0, 1.0};
    const vertex c = {0.0, 0.0};
    polygon<3> p(a, b, c);

    georhiau::algo::ear_clip(p);
}
