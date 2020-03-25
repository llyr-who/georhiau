#include "core/edge.hpp"

#include <set>

#include "gtest/gtest.h"

using edge_2d = georhiau::core::edge<double, 2>;
using vert_2d = georhiau::core::vertex<double, 2>;

TEST(edge, rotate) {
    vert_2d a = {1.0, 1.0};
    vert_2d b = {1.0, 3.0};
    edge_2d e(a, b);
    auto e_rot = georhiau::core::rotate(e);
    vert_2d c = {0.0, 2.0};
    vert_2d d = {2.0, 2.0};
    edge_2d e_rot_exp(c, d);
    ASSERT_EQ(e_rot, e_rot_exp);
}

TEST(edge, intersect) {
    vert_2d a = {1.0, 1.0};
    vert_2d b = {1.0, 3.0};
    edge_2d e1(a, b);
    vert_2d c = {0.0, 2.0};
    vert_2d d = {2.0, 2.0};
    edge_2d e2(c, d);

    auto [how, where] = georhiau::core::intersect(e1, e2);

    ASSERT_NEAR(where, 0.5, 1e-6);
    ASSERT_EQ(how, edge_2d::intersection::Skew);
}

TEST(edge, less_than) {
    vert_2d a = {1.0, 1.0};
    vert_2d b = {1.0, 3.0};
    edge_2d e1(a, b);
    vert_2d c = {0.0, 2.0};
    vert_2d d = {2.0, 2.0};
    edge_2d e2(c, d);

    ASSERT_TRUE(e2 < e1);
}

// After multiple failures on other tests and examples, we need to check
// whether std::find or CONTAINER.find(something) works on various C++
// containers.

TEST(edge, find) {
    vert_2d a = {1.0, 1.0};
    vert_2d b = {2.0, 1.0};
    vert_2d c = {1.0, 2.0};

    edge_2d e1(a, b);
    edge_2d e2(b, c);
    edge_2d e3(c, a);

    std::set<edge_2d> s;
    s.insert(e1);
    s.insert(e2);
    s.insert(e3);

    auto it1 = s.find(e1);
    ASSERT_TRUE(it1 != s.end());
}

