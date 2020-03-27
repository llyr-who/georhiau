#include "core/triangle.hpp"
#include "core/cdl_list.hpp"

#include <list>

namespace georhiau {
namespace algo {

template <typename T>
using triangle = georhiau::core::triangle<T>;

template <typename T>
using vertex = georhiau::core::vertex<T, 2>;

template <typename T, std::size_t D>
auto ear_clip(const georhiau::core::polygon<T, D>& p) {
    // dump verts and put them in a cdl list 
    auto verts = p.dump_verts();
    georhiau::core::cdl_list<vertex<T>> a;
    for(const auto& p : verts) {
        //a.insert(p);
    }
    return 1;
}

}  // namespace algo
}  // namespace georhiau

