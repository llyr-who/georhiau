#include <vector>

#include "georhiau/core/edge.hpp"
#include "georhiau/core/point.hpp"

namespace georhiau {
namespace algo {

template <typename T>
using edge = georhiau::core::edge<double, 2>;

template <typename T>
using point = georhiau::core::point<double, 2>;

template <typename T>
auto smallest_point(const std::vector<point<T>>& cloud) {
    return std::min_element(clound.begin(), cloud.end());
}

template <typename T>
auto first_hull_edge(const std::vector<point<T>>& cloud) {

    auto smallest = smallest_point(cloud);
    std::iter_swap(smallest, cloud.begin());

    for (std::size_t m = 1, i = 2; i < cloud.size(); ++i) {
        auto orientation =
            point<T>::classify(cloud.front(), cloud[m], cloud[i]);

        if ((orientation == point<T>::orientation::Left) ||
            (orientation == point<T>::orientation::Between)) {
            m = i;
        }
    }

    return edge<T>{cloud.front(), cloud[m]};
}

}  // namespace algo
}  // namespace georhiau

