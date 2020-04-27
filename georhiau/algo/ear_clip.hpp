#pragma once

#include "core/cdl_list.hpp"
#include "core/triangle.hpp"

#include <list>
#include <vector>

namespace georhiau {

using triangle_d = georhiau::triangle<double>;
using vertex_d = georhiau::vertex<double, 2>;
using vertex_d_list = georhiau::cdl_list<vertex_d>;

// this routine can probably be pulled out of here.
bool convex(const vertex_d& a, const vertex_d& b, const vertex_d& c) {
    if (georhiau::classify(a, c, b) == vertex_d::orientation::Right) {
        return true;
    }
    return false;
}

// this routine can probably be pulled out of here.
bool inside_triangle(const vertex_d& p, const vertex_d& t_a,
                     const vertex_d& t_b, const vertex_d& t_c) {
    // in this case, b is the ear.
    // we want to look at the parametric equation
    // for a point in 2D with respect to a basis
    // formed by ba and v1, and origin b ( the ear ).
    //
    vertex_d v0 = t_a - t_b;
    vertex_d v1 = t_c - t_b;
    vertex_d v2 = p - t_b;

    // p = b  + u * v0 + v * v1.
    // we want to find u and v.
    auto norm_v0 = v0 * v0;
    auto norm_v1 = v1 * v1;
    auto v0_v1 = v0 * v1;
    auto v2_v1 = v2 * v1;
    auto v2_v0 = v2 * v0;
    auto denom = norm_v0 * norm_v1 - v0_v1 * v0_v1;

    auto u = (norm_v1 * v2_v0 - v0_v1 * v2_v1) / denom;
    auto v = (norm_v0 * v2_v1 - v0_v1 * v2_v0) / denom;

    if (u < 0 || v < 0 || u > 1 || v > 1 || (u + v) > 1) return false;
    return true;
}

// the following routines are heavily linked to the implementation
// of the circ. linked list that we have used. This is quite bad
// design and needs to change

bool ear(vertex_d_list::iterator& ear, vertex_d_list& vl) {
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

auto ear_clip(const std::vector<vertex_d>& verts) {
    std::list<triangle_d> tris;
    // dump verts and put them in a cdl list
    vertex_d_list vert_list;
    for (const auto& p : verts) {
        vert_list.push_back(p);
    }

    auto v = vert_list.end();

    while (vert_list.size() > 2) {
        if ((v).itr_node == vert_list.root) ++v;
        auto a = vert_list.prev(v)->data;
        auto b = v->data;
        auto c = vert_list.next(v)->data;

        if (!convex(a, b, c)) continue;
        if (!ear(v, vert_list)) continue;

        // now we can handle the ear
        tris.push_back(triangle_d{a, b, c});
        vert_list.erase(v);
        ++v;
    }

    return tris;
}  // namespace algo

}  // namespace georhiau

