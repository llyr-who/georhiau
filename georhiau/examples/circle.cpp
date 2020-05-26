#include <iostream>
#include <vector>

#include "algo/delaunay.hpp"
#include "core/vertex.hpp"
#include "plot/plot.hpp"

using vertex = georhiau::vertex<double, 2>;
double pi() { return std::atan(1) * 4; }

int main() {
    std::vector<vertex> cloud;

    std::size_t N = 10;
    for (std::size_t i = 0; i < N; ++i) {
        double t = 2.0 * pi() * i * (1.0 / static_cast<double>(N));
        cloud.push_back(vertex{1.0 + std::cos(t), 1.0 + std::sin(t)});
    }
    cloud.push_back(vertex{1.0, 1.0});

    std::cout << "input cloud" << std::endl;
    std::cout << cloud.size() << std::endl;
    auto tris = georhiau::delaunay(cloud);

    std::cout << "Number of triangles" << std::endl;
    std::cout << tris.size() << std::endl;

    int i = 0;
    double area = 0.0;
    for (const auto& t : tris) {
        area += georhiau::area(t);
    }

    std::cout << "total area of triangles: " << area << std::endl;
    std::cout << "expected area (area of unit circle): " << pi() << std::endl;

    georhiau::plot(tris);
    georhiau::show_plots();
}
