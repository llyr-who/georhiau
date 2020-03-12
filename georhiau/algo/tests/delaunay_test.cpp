#include "algo/delaunay.hpp"

#include "gtest/gtest.h"

using vertex = georhiau::core::vertex<double, 2>;

TEST(delaunay, single_element_mesh) {
    vertex a = {0.0, 0.0};
    vertex b = {2.0, 0.0};
    vertex c = {2.0, 2.0};

    std::vector<vertex> cloud = {a,b,c};

    georhiau::algo::delaunay(cloud);
}

