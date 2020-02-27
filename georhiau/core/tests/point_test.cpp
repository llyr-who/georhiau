#include "core/point.hpp"

#include "gtest/gtest.h"

using point_2d = georhiau::core::point<double, 2>;

TEST(point, less_than) {
    point_2d a = {1.0, 1.0};
    point_2d b = {2.0, 1.0};
    point_2d c = {0.0, 1.0};
    ASSERT_TRUE(a < b);
    ASSERT_FALSE(b < c);
}
