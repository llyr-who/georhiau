#pragma once

#include <GLFW/glfw3.h>
#include <iostream>
#include <limits>
#include <list>
#include <random>

#include "algo/delaunay.hpp"
#include "core/triangle.hpp"

// we are using the dreadfull old OpenGl ways.
// That is, we are not using vertex array buffers.
// The main reason behind this is that I can not
// decide on a extension loading library lol. 
//
// We could...
// a) write our own (been there and done that) (fav choice)
// b) use glad (envolves the user and compiling something ( I think )


// THEN
// we need to deal with this mess. A soup of C-style routines.
// Design a plot object and use factory method to plot multiple things

// THESE WILL BECOME PRIVATE MEMBER VARS
static int w = 0;
static int h = 0;

namespace georhiau {
namespace view {

static void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action,
                         int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

// returns scaling factors for glOrtho
auto projection_params(std::list<georhiau::core::triangle<double>>& tris) {
    auto max_w = 0.0;
    auto max_h = 0.0;

    for (const auto& t : tris) {
        for (std::size_t i = 0; i < 3; ++i) {
            if (t[i][0] > max_w) max_w = t[i][0];
            if (t[i][1] > max_h) max_h = t[i][1];
        }
    }
    return std::make_pair(max_w, max_h);
}

void draw_triangles(std::list<georhiau::core::triangle<double>>& tris) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    auto params = projection_params(tris);

    glOrtho(0.0f, params.first * (1.01), 0.0f, params.second * (1.01), 0.f,
            1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    for (const auto& t : tris) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBegin(GL_TRIANGLES);
        glColor3f(0.1f, 0.0f, 0.0f);
        glVertex2f(t[0][0], t[0][1]);
        glVertex2f(t[1][0], t[1][1]);
        glVertex2f(t[2][0], t[2][1]);
        glEnd();
    }
}

bool run(GLFWwindow* window,
         std::list<georhiau::core::triangle<double>>& tris) {
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.98f, 0.98f, 0.98f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        draw_triangles(tris);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return true;
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

auto plot(std::list<georhiau::core::triangle<double>>& tris) {
    auto window = get_window();
    if (window) {
        auto finished = run(window, tris);
    }
    exit(window);
}

}  // namespace view
}  // namespace georhiau
