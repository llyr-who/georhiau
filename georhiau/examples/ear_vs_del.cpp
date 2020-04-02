#include "algo/delaunay.hpp"
#include "algo/ear_clip.hpp"
#include "view/plot.hpp"

int main() {
    using vertex = georhiau::core::vertex<double, 2>;

    vertex a = {1.0, 5.0};
    vertex b = {1.0, 1.0};
    vertex c = {3.0, 1.0};
    vertex d = {3.0, 3.0};

    std::vector<vertex> cloud = {a,b,c,d};

    //auto tris = georhiau::algo::delaunay(cloud);
    //georhiau::view::plot(tris);
    auto tris = georhiau::algo::ear_clip(cloud);
    georhiau::view::plot(tris);
}

