#include "algo/ear_clip.hpp"

#include "gtest/gtest.h"

using vertex = georhiau::vertex<double, 2>;

template <std::size_t N>
using polygon = georhiau::polygon<double, N>;

TEST(ear_clip, convex) {
    vertex a = {0.0, 0.0};
    vertex b = {1.0, 0.0};
    vertex c = {1.0, 1.0};

    ASSERT_TRUE(georhiau::convex(a, b, c));
}

TEST(ear_clip, inside_triangle) {
    vertex a = {0.0, 0.0};
    vertex b = {1.0, 2.0};
    vertex c = {2.0, 0.0};

    vertex p = {1.0, 1.0};
    vertex q = {10.0, 1.0};

    ASSERT_TRUE(georhiau::inside_triangle(p, a, b, c));
    ASSERT_FALSE(georhiau::inside_triangle(q, a, b, c));

    a = {3.0, 3.0};
    b = {1.0, 5.0};
    c = {1.0, 1.0};

    p = {3.0, 1.0};
    ASSERT_FALSE(georhiau::inside_triangle(p, a, b, c));
}

TEST(ear_clip, basic) {
    vertex a = {0.0, 0.0};
    vertex b = {1.0, 0.0};
    vertex c = {1.0, 1.0};
    vertex d = {0.0, 1.0};
    std::vector<vertex> p = {a, b, c, d};

    auto tris = georhiau::ear_clip(p);

    ASSERT_EQ(tris.size(), 2);
}

double pi() { return std::atan(1) * 4; }

TEST(ear_clip, hexagon) {
    std::vector<vertex> cloud;
    std::size_t N = 6;
    for (std::size_t i = 0; i < N; ++i) {
        double t = 2.0 * pi() * i * (1.0 / static_cast<double>(N));
        cloud.push_back(vertex{std::cos(t), std::sin(t)});
    }

    auto tris = georhiau::ear_clip(cloud);
    ASSERT_EQ(tris.size(), 4);
}
