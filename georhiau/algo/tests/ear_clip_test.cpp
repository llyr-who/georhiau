#include "algo/ear_clip.hpp"

#include "gtest/gtest.h"

using vertex = georhiau::core::vertex<double, 2>;

template <std::size_t N>
using polygon = georhiau::core::polygon<double, N>;

TEST(ear_clip, convex) {
    vertex a = {0.0, 0.0};
    vertex b = {1.0, 0.0};
    vertex c = {1.0, 1.0};

    ASSERT_TRUE(georhiau::algo::convex(a, b, c));
}

TEST(ear_clip, inside_triangle) {
    vertex a = {0.0, 0.0};
    vertex b = {1.0, 2.0};
    vertex c = {2.0, 0.0};

    vertex p = {1.0, 1.0};
    vertex q = {10.0, 1.0};

    ASSERT_TRUE(georhiau::algo::inside_triangle(p, a, b, c));
    ASSERT_FALSE(georhiau::algo::inside_triangle(q, a, b, c));
}

TEST(ear_clip, basic) {
    vertex a = {0.0, 0.0};
    vertex b = {1.0, 0.0};
    vertex c = {1.0, 1.0};
    vertex d = {0.0, 1.0};
    polygon<4> p(a, b, c, d);

    auto tris = georhiau::algo::ear_clip(p);

    ASSERT_EQ(tris.size(), 2);

    std::cout << "DEBUG" << std::endl;
    for(const auto& t : tris) {
        std::cout << " ----- " << std::endl;
        georhiau::core::print(t);
    }
}
