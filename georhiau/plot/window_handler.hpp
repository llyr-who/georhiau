#pragma once

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

#include <mutex>
#include <thread>
#include <utility>
#include <vector>

#include "plot/geom.hpp"
#include "plot/window.hpp"

namespace georhiau {
namespace plt {
class window_handler {
public:
    // create singleton
    static window_handler& Instance() {
        static window_handler wh;
        return wh;
    }

    // add window to list
    void add_window(std::shared_ptr<figure_window> w,
                    const std::list<vertex<double, 2>>& itms) {
        ver_win_.push_back(std::pair(w, itms));
    }

    void add_window(std::shared_ptr<figure_window> w,
                    const std::list<triangle<double>>& itms) {
        tri_win_.push_back(std::pair(w, itms));
    }

    void add_window(std::shared_ptr<figure_window> w,
                    const std::list<edge<double, 2>>& itms) {
        edg_win_.push_back(std::pair(w, itms));
    }

    void handle_windows() {
        while (ver_win_.size() != 0 || edg_win_.size() != 0 ||
               tri_win_.size() != 0) {
            for (int i = 0; i < edg_win_.size(); i++) {
                auto w = edg_win_[i];
                if (w.first->windowShouldClose()) {
                    edg_win_.erase(edg_win_.begin() + i);
                    continue;
                }
                w.first->run<edge<double, 2>>(w.second);
            }
            for (int i = 0; i < ver_win_.size(); i++) {
                auto w = ver_win_[i];
                if (w.first->windowShouldClose()) {
                    ver_win_.erase(ver_win_.begin() + i);
                    continue;
                }
                w.first->run<vertex<double, 2>>(w.second);
            }
            for (int i = 0; i < tri_win_.size(); i++) {
                auto w = tri_win_[i];
                if (w.first->windowShouldClose()) {
                    tri_win_.erase(tri_win_.begin() + i);
                    continue;
                }
                w.first->run<triangle<double>>(w.second);
            }
        }
        glfwTerminate();
    }

private:
    std::vector<
        std::pair<std::shared_ptr<figure_window>, std::list<vertex<double, 2>>>>
        ver_win_;
    std::vector<
        std::pair<std::shared_ptr<figure_window>, std::list<edge<double, 2>>>>
        edg_win_;
    std::vector<
        std::pair<std::shared_ptr<figure_window>, std::list<triangle<double>>>>
        tri_win_;
};

auto& wndw_hndlr = window_handler::Instance();
}  // namespace plt
}  // namespace georhiau
