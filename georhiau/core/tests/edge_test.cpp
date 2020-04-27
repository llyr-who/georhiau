#include "core/edge.hpp"

#include <set>

#include "gtest/gtest.h"

using edge_2d = georhiau::edge<double, 2>;
using vert_2d = georhiau::vertex<double, 2>;

TEST(edge, rotate) {
    vert_2d a = {1.0, 1.0};
    vert_2d b = {1.0, 3.0};
    edge_2d e(a, b);
    auto e_rot = georhiau::rotate(e);
    vert_2d c = {0.0, 2.0};
    vert_2d d = {2.0, 2.0};
    edge_2d e_rot_exp(c, d);
    ASSERT_EQ(e_rot, e_rot_exp);
}

TEST(edge, intersect_basic) {
    vert_2d a = {1.0, 1.0};
    vert_2d b = {1.0, 3.0};
    edge_2d e1(a, b);
    vert_2d c = {0.0, 2.0};
    vert_2d d = {2.0, 2.0};
    edge_2d e2(c, d);

    auto [how, where] = georhiau::intersect(e1, e2);

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

// This test essentially tests the implementation of
// the < operator and shows that it behaves as we
// expect it to.
TEST(edge, find_set) {
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

// similar to above.
TEST(edge, pop_min_set) {
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

    s.erase(s.begin());
    auto it1 = s.find(e1);
    ASSERT_TRUE(it1 == s.end());
}

double pi() { return std::atan(1) * 4; }

// this test highlights that we need to get dirty with
// magic numbers in "intersect"
TEST(edge, intersect_bug) {
    std::vector<vert_2d> cloud;

    std::size_t N = 10;
    for (std::size_t i = 0; i < N; ++i) {
        double t = 2.0 * pi() * i * (1.0 / static_cast<double>(N));
        cloud.push_back(vert_2d{std::cos(t), std::sin(t)});
    }

    auto centre = vert_2d{0.0, 0.0};

    for (std::size_t i = 0; i < 5; ++i) {
        auto p = cloud[i];
        auto ap = cloud[i + 5];
        auto e1 = edge_2d(centre, p);
        auto e2 = edge_2d(centre, ap);
        georhiau::print(e1);
        georhiau::print(e2);
        ASSERT_EQ(intersect(e1, e2).first, edge_2d::intersection::Colinear);
    }
}

