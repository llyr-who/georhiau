#include <random>

#include "plot/plot.hpp"
#include "algo/delaunay.hpp"

int main() {
    using vtx = georhiau::vertex<double, 2>;

    std::random_device dev;
    std::mt19937 rng(dev());

    // generate points between 0 and 10.
    std::uniform_real_distribution<> dist(0.1, 9.9);

    std::vector<vtx> cloud;

    for (std::size_t i = 0; i < 10000; ++i) {
        auto x = dist(rng);
        auto y = dist(rng);
        if ((x - 5) * (x - 5) + (y - 5) * (y - 5) < 5.0) {
            vtx v{x, y};
            cloud.push_back(v);
        }
    }

    auto tris = georhiau::delaunay(cloud);

    georhiau::plot(tris);
    georhiau::show_plots();
}

