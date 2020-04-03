#include <random>

#include "algo/delaunay.hpp"
#include "algo/inc_trgtn.hpp"
#include "view/plot.hpp"

int main() {
    using vtx = georhiau::core::vertex<double, 2>;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<> dist(0.1, 9.9);

    std::vector<vtx> cloud;

    for (std::size_t i = 0; i < 10; ++i) {
        vtx v{dist(rng), dist(rng)};
        cloud.push_back(v);
        std::cout << v[0] << " " << v[1] << std::endl;
    }

    georhiau::algo::inc_trgtn(cloud);

}

