#pragma once

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

#include <GLFW/glfw3.h>

#include <any>

#include "plot/geom.hpp"

namespace georhiau {
namespace plt {
class figure_window {
private:
    GLFWwindow* wndw_;

    int w_ = 0;
    int h_ = 0;

    auto resolution() {
        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        return std::make_pair(mode->width, mode->height);
    }

    static void error_callback(int error, const char* description) {
        fprintf(stderr, "Error: %s\n", description);
    }

    static void key_callback(GLFWwindow* window, int key, int scancode,
                             int action, int mods) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);
    }

public:
    figure_window() {
        // Set error callback, just in case we encounter
        // any errors before/during window creation and
        // glfw initialisation.
        glfwSetErrorCallback(error_callback);
        glfwInit();
       
        #ifdef __APPLE__
        // added to ensure resolution() returns correct values for MacOS
        glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
        #endif

        // Obtain monitor resolution.
        auto res = resolution();
        // We want to take up one quarter of screen space
        // and we want the plot to be square
        w_ = res.first / 4;
        h_ = res.first / 4;

        wndw_ = glfwCreateWindow(w_, h_, "GeoRhiau", nullptr, nullptr);
        if (!wndw_) {
            return;
        }

        glfwSetKeyCallback(wndw_, key_callback);
        glfwMakeContextCurrent(wndw_);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glPointSize(5);

        return;
    }

    ~figure_window() {
        if (wndw_) {
            glfwDestroyWindow(wndw_);
        }
    }

    bool windowShouldClose() { return glfwWindowShouldClose(wndw_); }

    template <typename T>
    void run(std::list<T> items) {
        glfwMakeContextCurrent(wndw_);

        glClearColor(0.98f, 0.98f, 0.98f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glViewport(0, 0, w_, h_);
        draw(items);

        glfwSwapBuffers(wndw_);
        glfwPollEvents();
    }
};
}  // namespace plt
}  // namespace georhiau
