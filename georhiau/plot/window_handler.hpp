#pragma once

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

#include <GLFW/glfw3.h>

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
    void add_window(figure_window* w) {
        std::lock_guard<std::mutex> lk(m_);

        wndws_.push_back(w);

        if (thread_init_ == false) {
            std::thread handle_thread(&window_handler::handle_windows, this);
            thread_init_ = true;
        }
    }

private:
    std::vector<figure_window*> wndws_;

    bool thread_init_ = false;
    std::mutex m_;

    void handle_windows() {
        while (wndws_.size() != 0) {
            for (int i = 0; i < wndws_.size(); i++) {
                auto w = wndws_[i];
                if (w->windowShouldClose()) {
                    wndws_.erase(wndws_.begin() + i);
                    continue;
                }
                w->run();
                glViewport(0, 0, w->width(), w->height());
                // draw();
            }
        }
    }
};

auto& wndw_hndlr = window_handler::Instance();
}  // namespace plt
}  // namespace georhiau
