#include "core/vertex.hpp"

#include "gtest/gtest.h"

using vertex_2d = georhiau::core::vertex<double, 2>;

TEST(vertex, less_than) {
    vertex_2d a = {1.0, 1.0};
    vertex_2d b = {2.0, 1.0};
    vertex_2d c = {0.0, 1.0};
    ASSERT_TRUE(a < b);
    ASSERT_FALSE(b < c);
}
