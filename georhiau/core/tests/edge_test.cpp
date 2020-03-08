#include "core/edge.hpp"

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
