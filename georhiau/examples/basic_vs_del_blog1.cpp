#include <random>

#include "algo/delaunay.hpp"
#include "algo/inc_trgtn.hpp"
#include "plot/plot.hpp"

int main() {
    using vtx = georhiau::vertex<double, 2>;

    /*
    vtx a = {1.0, 1.5};
    vtx b = {0.5, 3.0};
    vtx c = {3.0, 3.0};
    vtx e = {2.0, 2.0};
    vtx f = {1.5, 4.0};

    std::vector<vtx> cloud = {a, b, c, e, f};
    */
    vtx d = {1.0, 0.5};
    vtx a = {2.0, 1.0};
    vtx b = {1.0, 2.0};
    vtx c = {3.0, 1.0};

    std::vector<vtx> cloud = {a, b, c, d};

    auto tris = georhiau::inc_trgtn(cloud);
    georhiau::plot(tris);
    tris = georhiau::delaunay(cloud);
    georhiau::plot(tris);
    georhiau::show_plots();
}

