#pragma once

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

#include <GLFW/glfw3.h>

namespace georhiau {

static int w = 0;
static int h = 0;

static void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action,
                         int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

auto exit(GLFWwindow* window) {
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

auto resolution() {
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    return std::make_pair(mode->width, mode->height);
}

auto get_window() {
    // Set error callback, just in case we encounter
    // any errors before/during window creation and
    // glfw initialisation.
    glfwSetErrorCallback(error_callback);
    glfwInit();

    // added to ensure resolution() returns correct values for MacOS
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);

    // Obtain monitor resolution.
    auto res = resolution();
    // We want to take up one quarter of screen space
    // and we want the plot to be square
    w = res.first / 4;
    h = res.first / 4;

    auto window = glfwCreateWindow(w, h, "GeoRhiau", nullptr, nullptr);
    if (!window) {
        return window;
    }

    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPointSize(5);

    return window;
}

}  // namespace georhiau
