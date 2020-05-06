#pragma once

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

#include <GLFW/glfw3.h>

#include <list>

#include "view/geom.hpp"
#include "view/window.hpp"

namespace georhiau {

template <typename T>
auto plot(const std::list<T>& items) {
    auto window = get_window();
    if (window) {
        auto finished = run(window, items);
    }
    exit(window);
}

template <typename T>
bool run(GLFWwindow* window, const std::list<T>& items) {
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.98f, 0.98f, 0.98f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        draw(items);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return true;
}

}  // namespace georhiau
