#include "algo/giftwrap.hpp"
#include "core/edge.hpp"

#include "view/plot.hpp"

#include "gtest/gtest.h"

#include <list>
#include <vector>
using vertex = georhiau::core::vertex<double, 2>;
using edge = georhiau::core::edge<double, 2>;
using point_cloud = std::vector<vertex>;

const point_cloud cloud1 = {{1.0, 5.0}, {2.0, 2.0}, {3.0, 3.0},
                            {0.0, 1.0}, {3.0, 2.0}, {10.0, 3.0},
                            {5.0, 1.0}, {8.0, 0.5}, {14.0, 3.0}};

using georhiau::algo::first_hull_edge;
using georhiau::algo::left_most_edge;

TEST(giftwrap, left_most_edge) {
    auto e1 = left_most_edge(cloud1[3], cloud1);
    auto e2 = left_most_edge(e1.dest(), cloud1);
    auto e3 = left_most_edge(e2.dest(), cloud1);

    std::list<edge> edges = {e1, e2, e3};
    georhiau::view::plot(edges);
}

TEST(giftwrap, first_hull_edge) {
    auto hull_edge = first_hull_edge<double>(cloud1);
    edge hull_edge_ans(cloud1[3], cloud1[0]);
    ASSERT_EQ(hull_edge, hull_edge_ans);
}
