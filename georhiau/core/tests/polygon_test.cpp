#include "core/polygon.hpp"

#include "gtest/gtest.h"

template <std::size_t N>
using polygon = georhiau::core::polygon<double, N>;

using vertex = georhiau::core::vertex<double, 2>;

TEST(polygon, construction) {
    vertex a = {1.0, 1.0};
    vertex b = {1.0, 2.0};
    vertex c = {2.0, 2.0};

    // generate polygon
    polygon<3> pol = {a, b, c};

    // dump verts
    auto vs = pol.dump_verts();
    polygon<3>::vertices va = {a,b,c};

    // are they equal
    ASSERT_TRUE(vs == va);
}
