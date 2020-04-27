#include "algo/rng.hpp"
#include "core/triangle.hpp"

#include "gtest/gtest.h"

using vertex = georhiau::vertex<double, 2>;
using edge = georhiau::edge<double, 2>;

TEST(rng, basic) {
    vertex a = {0.0, 0.0};
    vertex b = {2.0, 0.0};
    vertex c = {2.0, 2.0};

    std::vector<vertex> cloud = {a, b, c};

    auto rng = georhiau::rng(cloud);

    ASSERT_EQ(rng.size(), 4);

    edge e1(a, b), e2(b, a), e3(b, c), e4(c, b);

    ASSERT_TRUE(std::find(rng.begin(), rng.end(), e1) != rng.end());
    ASSERT_TRUE(std::find(rng.begin(), rng.end(), e2) != rng.end());
    ASSERT_TRUE(std::find(rng.begin(), rng.end(), e3) != rng.end());
    ASSERT_TRUE(std::find(rng.begin(), rng.end(), e4) != rng.end());
}

