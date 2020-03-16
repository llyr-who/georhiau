#include "algo/delaunay.hpp"

#include "core/triangle.hpp"
#include "gtest/gtest.h"

using vertex = georhiau::core::vertex<double, 2>;

TEST(delaunay, single_element_mesh) {
    const vertex a = {0.0, 0.0};
    const vertex b = {2.0, 0.0};
    const vertex c = {2.0, 2.0};

    std::vector<vertex> cloud = {a, b, c};

    auto tngltn = georhiau::algo::delaunay(cloud);

    georhiau::core::triangle<double> t = {a, b, c};

    ASSERT_EQ(tngltn.size(), 1);
    ASSERT_EQ(tngltn.front(), t);
}

