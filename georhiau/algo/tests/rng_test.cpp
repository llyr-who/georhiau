#include "algo/rng.hpp"
#include "core/triangle.hpp"

#include "gtest/gtest.h"

using vertex = georhiau::core::vertex<double, 2>;

TEST(rng, basic) {
    vertex a = {0.0, 0.0};
    vertex b = {2.0, 0.0};
    vertex c = {2.0, 2.0};

    std::vector<vertex> cloud = {a, b, c};

    auto rng = georhiau::algo::rng(cloud);
    ASSERT_EQ(rng.size(), 4);
}

