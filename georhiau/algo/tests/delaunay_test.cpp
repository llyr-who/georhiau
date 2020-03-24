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

TEST(delaunay, square) {
    const vertex a = {0.0, 0.0};
    const vertex b = {2.0, 0.0};
    const vertex c = {2.0, 2.0};
    const vertex d = {0.0, 2.0};

    std::vector<vertex> cloud = {a, b, c, d};

    auto tngltn = georhiau::algo::delaunay(cloud);

    georhiau::core::triangle<double> t1 = {a, b, d};
    georhiau::core::triangle<double> t2 = {d, b, c};

    auto it1 = std::find(tngltn.begin(), tngltn.end(), t1);
    auto it2 = std::find(tngltn.begin(), tngltn.end(), t2);

    ASSERT_FALSE(it1 == tngltn.end());
    ASSERT_FALSE(it2 == tngltn.end());

    ASSERT_EQ(tngltn.size(), 2);
}

double pi() { return std::atan(1)*4; }

TEST(delaunay, circle) {
    std::vector<vertex> cloud1;
    std::size_t N = 3;
    for (std::size_t i = 0; i < N; ++i) {
        double t = 2.0 * pi() * i * (1.0/static_cast<double>(N));
        cloud1.push_back(vertex{std::cos(t), std::sin(t)});
    }
    cloud1.push_back(vertex{0.0, 0.0});

    ASSERT_EQ(4,cloud.size());
    auto tris = georhiau::algo::delaunay(cloud);
    ASSERT_EQ(3,tris.size()));
}
