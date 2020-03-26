#include "georhiau/core/triangle.hpp"

namespace georhiau {
namespace algo {

template <typename T>
using triangle = georhiau::core::triangle<T>;

template <typename T>
auto ear_clip(std::vector<vertex<T>> a) {
    for (size_t t = a.size() - 1, i = 0, j = 1; i < a.size();
         t = i++, j = (i + 1) % a.size()) {
        if (a.size() == 3) {
            triangle t = {a[0], a[1], a[2]};
            mTriangles.push_back(t);
            break;
        }
        
        // is the ith vertex of a an ear?
        if (isEar(i, a)) {
            T.x = a[t].VertexNumber;
            T.y = a[i].VertexNumber;
            T.z = a[j].VertexNumber;

            // here we have the diagonals
            Edge d(a[j].VertexNumber, a[t].VertexNumber, 0);
            mEdges.push_back(d);
            mTriangles.push_back(T);
            a.erase(a.begin() + i, a.begin() + i + 1);
            t = a.size() - 1;
            i = 0;
            j = 1;
        }
    }
}
}  // namespace algo
}  // namespace georhiau

