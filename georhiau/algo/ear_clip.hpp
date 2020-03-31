
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

// this routine can probably be pulled out of here.
bool convex(const vertex& a, const vertex& b, const vertex& c) {
    if (georhiau::core::classify(a, c, b) == vertex::orientation::Right) {
        return true;
    }
    return false;
}

// this routine can probably be pulled out of here.
bool inside_triangle(const vertex& p, const vertex& t_a, const vertex& t_b,
                     const vertex& t_c) {
    // in this case, b is the ear.
    // we want to look at the parametric equation
    // for a point in 2D with respect to a basis
    // formed by ba and v1, and origin b ( the ear ).
    //
    vertex v0 = t_a - t_b;
    vertex v1 = t_c - t_b;
    vertex v2 = p - t_b;

    // p = b  + u * v0 + v * v1.
    // we want to find u and v.
    auto norm_v0 = v0 * v0;
    auto norm_v1 = v1 * v1;
    auto v0_v1 = v0 * v1;
    auto v2_v1 = v2 * v1;
    auto v2_v0 = v2 * v0;
    auto denom = norm_v0 * norm_v1 + v0_v1 * v0_v1;

    auto u = (norm_v1 * v2_v0 - v0_v1 * v2_v1) / denom;
    auto v = (norm_v0 * v2_v1 - v0_v1 * v2_v1) / denom;

    if (u < 0 || v < 0 || u > 1 || v > 1 || (u + v) > 1) return false;
    return true;
}

// the following routines are heavily linked to the implementation
// of the circ. linked list that we have used. This is quite bad
// design and needs to change

bool ear(vertex_list::iterator& ear, vertex_list& vl) {
    auto ear_next = vl.next(ear);
    auto curr = vl.next(ear_next);
    auto before_ear = vl.prev(ear);

    auto a = vl.prev(ear)->data;
    auto b = ear->data;
    auto c = vl.next(ear)->data;

    while (curr != before_ear) {
        if (inside_triangle(curr->data, a, b, c)) {
            return false;
        }
        curr = vl.next(curr);
    }

    return true;
}

template <std::size_t D>
auto ear_clip(const polygon<D>& p) {
    // dump verts and put them in a cdl list
    auto verts = p.dump_verts();
    vertex_list vert_list;
    for (const auto& p : verts) {
        vert_list.push_back(p);
    }

    auto v = vert_list.end();

    while (vert_list.size() > 2) {
        ++v;
        auto a = vert_list.prev(v)->data;
        auto b = v->data;
        auto c = vert_list.next(v)->data;

        if (!convex(a, b, c)) continue;
        if (!ear(v, vert_list)) continue;
        // now we can handle the ear
        vert_list.erase(v);
        if ((v).itr_node == vert_list.root) ++v;
    }
    return 1;
}

}  // namespace algo
}  // namespace georhiau

