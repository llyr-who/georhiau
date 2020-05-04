#include "algo/mate.hpp"

#include "gtest/gtest.h"

using vertex = georhiau::vertex<double, 2>;
using edge = georhiau::edge<double, 2>;

TEST(mate, basic) {
    // create point cloud
    vertex a = {1.0, 1.0};
    vertex b = {4.0, 3.0};
    vertex c = {3.0, 9.0};
    vertex d = {30.0, -1.0};
    vertex e = {3.0, -1.0};
    vertex f = {3.0, 6.0};
    std::vector<vertex> cloud = {a, b, c, d, e, f};

    // some edge
    vertex org = {0.0, 0.0};
    vertex dst = {0.0, 1.0};
    edge edg(org, dst);

    auto r1 = georhiau::mate<double>(edg, cloud);
    auto r2 = georhiau::mate2<double>(edg, cloud);
    // Does it get the correct answer?
    ASSERT_EQ(*r1, a);
    // Does it match the other one?
    ASSERT_EQ(*r1, *r2);
}

TEST(mate, single_triangle) {
    // create triangle point cloud
    vertex a = {0.0, 0.0};
    vertex b = {2.0, 0.0};
    vertex c = {2.0, 2.0};
    std::vector<vertex> cloud = {a, b, c};
    edge edg(a, c);

    auto r1 = georhiau::mate<double>(edg, cloud);
    auto r2 = georhiau::mate2<double>(edg, cloud);
    // Does it get the correct answer?
    ASSERT_EQ(*r1, b);
    // Does it match the other one?
    ASSERT_EQ(*r1, *r2);
}

double pi() { return std::atan(1) * 4; }

TEST(mate, circle) {
    std::vector<vertex> c0;
    std::size_t N = 3;
    for (std::size_t i = 0; i < N; ++i) {
        double t = 2.0 * pi() * i * (1.0 / static_cast<double>(N));
        c0.push_back(vertex{std::cos(t), std::sin(t)});
    }
    c0.push_back(vertex{0.0, 0.0});

    // exterior faces
    {
        edge e1(c0[0], c0[1]);
        auto em0 = georhiau::mate(e1, c0);
        auto em1 = georhiau::mate2(e1, c0);
        ASSERT_EQ(em0, c0.end());
        ASSERT_EQ(em1, c0.end());

        edge e2(c0[1], c0[2]);
        em0 = georhiau::mate(e2, c0);
        em1 = georhiau::mate2(e2, c0);
        ASSERT_EQ(em0, c0.end());
        ASSERT_EQ(em1, c0.end());

        edge e3(c0[2], c0[0]);
        em0 = georhiau::mate(e3, c0);
        em1 = georhiau::mate2(e3, c0);
        ASSERT_EQ(em0, c0.end());
        ASSERT_EQ(em1, c0.end());
    }

    // interior faces
    {
        edge e0(c0[3], c0[0]);
        auto em0 = georhiau::mate(e0, c0);
        auto em1 = georhiau::mate2(e0, c0);
        ASSERT_EQ(*em1, *em0);

        edge e1(c0[1], c0[0]);
        em0 = georhiau::mate(e1, c0);
        em1 = georhiau::mate2(e1, c0);
        ASSERT_EQ(*em1, *em0);

        edge e2(c0[2], c0[1]);
        em0 = georhiau::mate(e2, c0);
        em1 = georhiau::mate2(e2, c0);
        ASSERT_EQ(*em1, *em0);

        edge e3(c0[0], c0[2]);
        em0 = georhiau::mate(e3, c0);
        em1 = georhiau::mate2(e3, c0);
        ASSERT_EQ(*em1, *em0);

        edge e4(c0[0], c0[3]);
        em0 = georhiau::mate(e4, c0);
        em1 = georhiau::mate2(e4, c0);
        ASSERT_EQ(*em1, *em0);

        edge e5(c0[1], c0[3]);
        em0 = georhiau::mate(e5, c0);
        em1 = georhiau::mate2(e5, c0);
        ASSERT_EQ(*em1, *em0);

        edge e6(c0[2], c0[3]);
        em0 = georhiau::mate(e6, c0);
        em1 = georhiau::mate2(e6, c0);
        ASSERT_EQ(*em1, *em0);

        edge e7(c0[3], c0[2]);
        em0 = georhiau::mate(e7, c0);
        em1 = georhiau::mate2(e7, c0);
        ASSERT_EQ(*em1, *em0);

        edge e8(c0[3], c0[1]);
        em0 = georhiau::mate(e8, c0);
        em1 = georhiau::mate2(e8, c0);
        ASSERT_EQ(*em1, *em0);
    }

    // ASSERT_EQ(N + 1, cloud1.size());
    // auto tris1 = georhiau::delaunay(cloud1);
    // ASSERT_EQ(N, tris1.size());
    /*
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
        */
}

