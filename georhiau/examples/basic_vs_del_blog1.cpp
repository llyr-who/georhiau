#include "algo/delaunay.hpp"
#include "algo/ear_clip.hpp"
#include "view/plot.hpp"

int main() {
    using vertex = georhiau::core::vertex<double, 2>;

    // polygon 1
    vertex a = {0.1, 2.1};
    vertex b = {0.1, 0.1};
    vertex c = {2.0, 0.1};
    vertex d = {2.0, 2.0};
    std::vector<vertex> cloud1 = {a, b, c, d};

    // polygon 2
    a = {0.1, 1.9};
    std::vector<vertex> cloud2 = {a, b, c, d};

    auto tris = georhiau::algo::delaunay(cloud1);
    georhiau::view::plot(tris);
    tris = georhiau::algo::ear_clip(cloud1);
    georhiau::view::plot(tris);

    tris = georhiau::algo::delaunay(cloud2);
    georhiau::view::plot(tris);
    tris = georhiau::algo::ear_clip(cloud2);
    georhiau::view::plot(tris);
}

