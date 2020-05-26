#pragma once

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

#include <any>
#include <list>
#include <memory>

#include "plot/geom.hpp"
#include "plot/window.hpp"
#include "plot/window_handler.hpp"

namespace georhiau {

template <typename T>
auto plot(const std::list<T>& items) {
    auto w = std::make_shared<plt::figure_window>();
    plt::wndw_hndlr.add_window(w, items);
}

void show_plots() { plt::wndw_hndlr.handle_windows(); }

}  // namespace georhiau
