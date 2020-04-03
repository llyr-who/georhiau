#include <random>

#include "algo/delaunay.hpp"
#include "algo/inc_trgtn.hpp"
#include "view/plot.hpp"

int main() {
    using vtx = georhiau::core::vertex<double, 2>;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<> dist(0.1, 9.9);

    vtx a = {1.0, 3.0};
    vtx b = {6.0, 6.0};
    vtx c = {4.0, 6.0};
    vtx d = {4.0, 1.0};
    vtx e = {1.0, 3.0};
    vtx f = {3.0, 3.0};

    std::vector<vtx> cloud = {a, b, c, d, e, f};
    /*
        std::vector<vtx> cloud ;
        for (std::size_t i = 0; i < 4; ++i) {
            vtx v{dist(rng), dist(rng)};
            cloud.push_back(v);
            std::cout << v[0] << " " << v[1] << std::endl;
        }
    */
    auto tris = georhiau::algo::inc_trgtn(cloud);

    std::cout << tris.size() << std::endl;
    georhiau::view::plot(tris);
}

