#include <iostream>
#include <vector>

#include "algo/delaunay.hpp"
#include "core/vertex.hpp"

using vertex = georhiau::core::vertex<double, 2>;
double pi() { return std::atan(1)*4; }

int main() {
    std::vector<vertex> cloud;

    std::size_t N = 3;
    for (std::size_t i = 0; i < N; ++i) {
        double t = 2.0 * pi() * i * (1.0/static_cast<double>(N));
        cloud.push_back(vertex{std::cos(t), std::sin(t)});
    }
    cloud.push_back(vertex{0.0, 0.0});

    std::cout << "input cloud" << std::endl;
    std::cout << cloud.size() << std::endl;
    auto tris = georhiau::algo::delaunay(cloud);

    std::cout << "Number of triangles" << std::endl;
    std::cout << tris.size() << std::endl;
    int i = 0;
    for(const auto& t : tris) {
        std::cout << "triangle " << i++ << std::endl;
        georhiau::core::print(t);
        std::cout <<  std::endl;
        std::cout << "---------" <<  std::endl;
    }
}
