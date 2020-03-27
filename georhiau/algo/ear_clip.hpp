#include "core/cdl_list.hpp"
#include "core/triangle.hpp"

#include <list>

namespace georhiau {
namespace algo {

using triangle = georhiau::core::triangle<double>;
using vertex = georhiau::core::vertex<double, 2>;
using vertex_list = georhiau::core::cdl_list<vertex>;
template <std::size_t D>
using polygon = georhiau::core::polygon<double, D>;

bool convex(const vertex& a, const vertex& b, const vertex& c) {
    std::cout << "a : ";
    georhiau::core::print(a);
    std::cout << "b : ";
    georhiau::core::print(b);
    std::cout << "c : ";
    georhiau::core::print(c);
    std::cout << std::endl;
    if (georhiau::core::classify(a, c, b) == vertex::orientation::Right) {
        std::cout << "b is on right" << std::endl;
    }

    return true;
}

bool ear(vertex_list::iterator& it) { return true; }

template <std::size_t D>
auto ear_clip(const polygon<D>& p) {
    // dump verts and put them in a cdl list
    auto verts = p.dump_verts();
    vertex_list vert_list;
    for (const auto& p : verts) {
        vert_list.push_back(p);
    }

    std::cout << vert_list.size() << std::endl;
    auto v = vert_list.end();

    while (vert_list.size() > 2) {
        ++v;
        if (!convex(vert_list.prev(v)->data, v->data, vert_list.next(v)->data))
            continue;
        // if (!ear(v)) continue;
        // now we can handle the ear
        vert_list.erase(v);
        if ((v).itr_node == vert_list.root) ++v;
    }
    return 1;
}

}  // namespace algo
}  // namespace georhiau

