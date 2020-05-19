#pragma once

#include <list>
#include <variant>

#include "core/edge.hpp"
#include "core/triangle.hpp"

namespace georhiau {
namespace plt {
class item_container {
public:
    using items =
        std::variant<std::list<vertex<double, 2>>, std::list<edge<double, 2>>,
                     std::list<triangle<double>>>;

    template <typename T>
    void set_items(const std::list<T>& itms) {
        items_ = itms;
    }

private:
    items items_;
};
}  // namespace plt
}  // namespace georhiau
