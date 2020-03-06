#include "algo/giftwrap.hpp"

#include "core/edge.hpp"

#include "gtest/gtest.h"

TEST(giftwrap, smallest_vertex) {
    using vertex = georhiau::core::vertex<double, 2>;

    vertex v1 = {1.0, 1.0};
    vertex v2 = {2.0, 2.0};
    vertex v3 = {3.0, 3.0};
    std::vector<vertex> cloud{v1, v2, v3};

    ASSERT_EQ(georhiau::algo::smallest_vertex<double>(cloud), v1);
}

TEST(gitwrap, first_hull_edge) {
    using vertex = georhiau::core::vertex<double, 2>;
    using edge = georhiau::core::edge<double, 2>;

    vertex v1 = {1.0, 5.0};
    vertex v2 = {2.0, 2.0};
    vertex v3 = {3.0, 3.0};
    vertex v4 = {0.0, 1.0};
    vertex v5 = {3.0, 2.0};
    vertex v6 = {10.0, 3.0};

    std::vector<vertex> cloud{v1, v2, v3, v4, v5, v6};

    auto hull_edge = georhiau::algo::first_hull_edge<double>(cloud);
    edge hull_edge_ans(v4,v1);

    georhiau::core::print(hull_edge);
    georhiau::core::print(hull_edge_ans);

    ASSERT_EQ(hull_edge, hull_edge_ans);
}
