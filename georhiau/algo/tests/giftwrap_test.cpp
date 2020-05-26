#include "algo/giftwrap.hpp"
#include "core/edge.hpp"

#include "plot/plot.hpp"

#include "gtest/gtest.h"

#include <list>
#include <vector>
using vertex = georhiau::vertex<double, 2>;
using edge = georhiau::edge<double, 2>;
using point_cloud = std::vector<vertex>;

const point_cloud cloud1 = {{1.0, 5.0}, {2.0, 2.0}, {3.0, 3.0},
                            {0.0, 1.0}, {3.0, 2.0}, {10.0, 3.0},
                            {5.0, 1.0}, {8.0, 0.5}, {14.0, 3.0}};

using georhiau::first_hull_edge;
using georhiau::left_most_edge;

TEST(giftwrap, left_most_edge) {
    auto e1 = left_most_edge(cloud1[3], cloud1);
    auto e2 = left_most_edge(e1.dest(), cloud1);
    auto e3 = left_most_edge(e2.dest(), cloud1);
    auto e4 = left_most_edge(e3.dest(), cloud1);
    auto e1_exp = edge(cloud1[3], cloud1[0]);
    auto e2_exp = edge(cloud1[0], cloud1[8]);
    auto e3_exp = edge(cloud1[8], cloud1[7]);
    auto e4_exp = edge(cloud1[7], cloud1[3]);

    ASSERT_EQ(e1, e1_exp);
    ASSERT_EQ(e2, e2_exp);
    ASSERT_EQ(e3, e3_exp);
    ASSERT_EQ(e4, e4_exp);
}

TEST(giftwrap, first_hull_edge) {
    auto hull_edge = first_hull_edge<double>(cloud1);
    edge hull_edge_ans(cloud1[3], cloud1[0]);
    ASSERT_EQ(hull_edge, hull_edge_ans);
}

using georhiau::giftwrap;

TEST(giftwrap, giftwrap) {
    auto convex_hull = giftwrap(cloud1);
    auto e1_exp = edge(cloud1[3], cloud1[0]);
    auto e2_exp = edge(cloud1[0], cloud1[8]);
    auto e3_exp = edge(cloud1[8], cloud1[7]);
    auto e4_exp = edge(cloud1[7], cloud1[3]);

    std::list<edge> convex_hull_exp = {e1_exp, e2_exp, e3_exp, e4_exp};

    ASSERT_EQ(convex_hull, convex_hull_exp);
}
