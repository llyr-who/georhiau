#include "algo/mate.hpp"

#include "gtest/gtest.h"

using vertex = georhiau::core::vertex<double, 2>;
using edge = georhiau::core::edge<double, 2>;

TEST(mate, basic) {
    // create point cloud
    vertex a = {1.0, 1.0};
    vertex b = {4.0, 3.0};
    vertex c = {3.0, 9.0};
    vertex d = {30.0, -1.0};
    vertex e = {3.0, -1.0};
    vertex f = {3.0, 6.0};
    std::vector<vertex> cloud = {a, b, c, d, e, f};

    // some edge
    vertex org = {0.0, 0.0};
    vertex dst = {0.0, 1.0};
    edge edg(org, dst);

    auto r1 = georhiau::algo::mate<double>(edg, cloud);
    auto r2 = georhiau::algo::mate2<double>(edg, cloud);
    // Does it get the correct answer?
    ASSERT_EQ(*r1, a);
    // Does it match the other one?
    ASSERT_EQ(*r1, *r2);
}

