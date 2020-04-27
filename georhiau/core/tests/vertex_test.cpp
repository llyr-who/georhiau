#include "core/vertex.hpp"

#include "gtest/gtest.h"

using vertex_2d = georhiau::vertex<double, 2>;

TEST(vertex, less_than) {
    vertex_2d a = {1.0, 1.0};
    vertex_2d b = {2.0, 1.0};
    vertex_2d c = {0.0, 1.0};
    ASSERT_TRUE(a < b);
    ASSERT_FALSE(b < c);
}

TEST(vertex, multiply_by_const) {
    vertex_2d v = {1.0, 1.0};
    auto act_result = 10.0 * v;
    vertex_2d exp_result = {10.0, 10.0};
    ASSERT_EQ(act_result, exp_result);
}

TEST(vertex, cross_product) {
    vertex_2d a = {1.0, 1.0};
    vertex_2d b = {3.0, 2.0};

    ASSERT_EQ(-1.0, georhiau::cross(a,b));
}

TEST(vertex, classify) {
    vertex_2d a = {1.0, 1.0};
    vertex_2d b = {2.0, 2.0};
    // Any point with y > x should
    // be on the left. loab = "left of ab"
    vertex_2d loab_1 = {1.0, 3.0};
    ASSERT_EQ(georhiau::classify(a, b, loab_1),
              vertex_2d::orientation::Left);
    // etc
    vertex_2d roab_1 = {1.0, 0.0};
    ASSERT_EQ(georhiau::classify(a, b, roab_1),
              vertex_2d::orientation::Right);

    vertex_2d beyond_ab_1 = {4.0, 4.0};
    ASSERT_EQ(georhiau::classify(a, b, beyond_ab_1),
              vertex_2d::orientation::Beyond);

    vertex_2d behind_ab_1 = {-1.0, -1.0};
    ASSERT_EQ(georhiau::classify(a, b, behind_ab_1),
              vertex_2d::orientation::Behind);

    vertex_2d a_cp = {1.0, 1.0};
    ASSERT_EQ(georhiau::classify(a, b, a_cp),
              vertex_2d::orientation::Origin);

    vertex_2d b_cp = {2.0, 2.0};
    ASSERT_EQ(georhiau::classify(a, b, b_cp),
              vertex_2d::orientation::Destination);

    vertex_2d between = {1.5, 1.5};
    ASSERT_EQ(georhiau::classify(a, b, between),
              vertex_2d::orientation::Between);

    // think about edge cases ...
}
