#include "algo/delaunay.hpp"

#include "core/triangle.hpp"
#include "gtest/gtest.h"

using vertex = georhiau::vertex<double, 2>;

TEST(delaunay, single_element_mesh) {
    vertex a = {0.0, 0.0};
    vertex b = {2.0, 0.0};
    vertex c = {2.0, 2.0};

    std::vector<vertex> cloud = {a, b, c};

    auto tngltn = georhiau::delaunay(cloud);

    georhiau::triangle<double> t = {a, b, c};

    ASSERT_EQ(tngltn.size(), 1);
    ASSERT_EQ(tngltn.front(), t);
}

TEST(delaunay, square) {
    vertex a = {0.0, 0.0};
    vertex b = {2.0, 0.0};
    vertex c = {2.0, 2.0};
    vertex d = {0.0, 2.0};

    std::vector<vertex> cloud = {a, b, c, d};

    auto tngltn = georhiau::delaunay(cloud);

    georhiau::triangle<double> t1 = {a, b, d};
    georhiau::triangle<double> t2 = {d, b, c};

    auto it1 = std::find(tngltn.begin(), tngltn.end(), t1);
    auto it2 = std::find(tngltn.begin(), tngltn.end(), t2);

    ASSERT_FALSE(it1 == tngltn.end());
    ASSERT_FALSE(it2 == tngltn.end());

    ASSERT_EQ(tngltn.size(), 2);
}

double pi() { return std::atan(1) * 4; }

TEST(delaunay, circle) {
    std::vector<vertex> cloud1;
    std::size_t N = 3;
    for (std::size_t i = 0; i < N; ++i) {
        double t = 2.0 * pi() * i * (1.0 / static_cast<double>(N));
        cloud1.push_back(vertex{std::cos(t), std::sin(t)});
    }
    cloud1.push_back(vertex{0.0, 0.0});

    ASSERT_EQ(N + 1, cloud1.size());
    auto tris1 = georhiau::delaunay(cloud1);
    ASSERT_EQ(N, tris1.size());

    std::vector<vertex> cloud2;
    N = 10;
    for (std::size_t i = 0; i < N; ++i) {
        double t = 2.0 * pi() * i * (1.0 / static_cast<double>(N));
        cloud2.push_back(vertex{std::cos(t), std::sin(t)});
    }
    cloud2.push_back(vertex{0.0, 0.0});

    ASSERT_EQ(N + 1, cloud2.size());
    auto tris2 = georhiau::delaunay(cloud2);
    ASSERT_EQ(N, tris2.size());

    std::vector<vertex> cloud3;
    N = 1000;
    for (std::size_t i = 0; i < N; ++i) {
        double t = 2.0 * pi() * i * (1.0 / static_cast<double>(N));
        cloud3.push_back(vertex{std::cos(t), std::sin(t)});
    }
    cloud3.push_back(vertex{0.0, 0.0});

    ASSERT_EQ(N + 1, cloud3.size());
    auto tris3 = georhiau::delaunay(cloud3);
    ASSERT_EQ(N, tris3.size());
}
