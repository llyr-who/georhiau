#include <random>

#include "algo/rng.hpp"
#include "plot/plot.hpp"

int main() {
    using vtx = georhiau::vertex<double, 2>;

    std::random_device dev;
    std::mt19937 rng(dev());

    // generate points between 0 and 10.
    std::uniform_real_distribution<> dist(0.1, 9.9);

    std::vector<vtx> cloud;

    for (std::size_t i = 0; i < 100; ++i) {
        auto x = dist(rng);
        auto y = dist(rng);
        vtx v{x, y};
        cloud.push_back(v);
    }

    auto edges = georhiau::rng(cloud);
    georhiau::plot(edges);
    georhiau::show_plots();
}

