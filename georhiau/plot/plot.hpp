#pragma once

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

#include <GLFW/glfw3.h>

#include <any>
#include <list>

#include "plot/geom.hpp"
#include "plot/window.hpp"
#include "plot/window_handler.hpp"

namespace georhiau {

namespace plt {
class items {
public:
    virtual std::any get_items() = 0;
};

template <typename T>
class plottable_items : public items {
public:
    plottable_items(const std::list<T>& items) : items_(items){};
    std::any get_items() { return std::make_any<std::list<T>>(items_); }

private:
    std::list<T> items_;
};

}  // namespace plt

template <typename T>
auto plot(const std::list<T>& items) {
    plt::figure_window w;
    w.set_items<T>(items);
    //auto plt_items = plt::plottable_items<T>(items);
    //auto is = plt_items.get_items();
    plt::wndw_hndlr.add_window(&w);
}
}  // namespace georhiau
