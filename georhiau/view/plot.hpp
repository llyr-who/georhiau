#pragma once

#include <GLFW/glfw3.h>
#include <list>

#include "core/edge.hpp"
#include "core/triangle.hpp"

static int w = 0;
static int h = 0;

namespace georhiau {

static void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action,
                         int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

// returns scaling factors for glOrtho
auto projection_params(std::list<georhiau::triangle<double>>& tris) {
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

// returns scaling factors for glOrtho
auto projection_params(std::list<georhiau::edge<double, 2>>& es) {
    auto max_w = 0.0;
    auto max_h = 0.0;

    for (const auto& e : es) {
        auto o = e.orig();
        auto d = e.dest();
        if (o[0] > max_w) max_w = o[0];
        if (o[1] > max_h) max_h = o[1];
        if (d[0] > max_w) max_w = d[0];
        if (d[1] > max_h) max_h = d[1];
    }
    return std::make_pair(max_w, max_h);
}

auto projection_params(std::list<georhiau::vertex<double, 2>>& ps) {
    auto max_w = 0.0;
    auto max_h = 0.0;

    for (const auto& v : ps) {
        if (v[0] > max_w) max_w = v[0];
        if (v[1] > max_h) max_h = v[1];
    }
    return std::make_pair(max_w, max_h);
}

void draw(std::list<georhiau::triangle<double>>& tris) {
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

using georhiau::norm;
using georhiau::rotate;

void draw(std::list<georhiau::edge<double, 2>>& es) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    auto params = projection_params(es);

    glOrtho(0.0f, params.first * (1.01), 0.0f, params.second * (1.01), 0.f,
            1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    for (const auto& e : es) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(e.orig()[0], e.orig()[1]);
        glVertex2f(e.dest()[0], e.dest()[1]);
        glEnd();
        // we want to draw a triangle to
        // indicate directedness
        auto mp = e.midpoint();
        auto bm = e.orig() - mp;
        auto s = 0.1 / norm(bm);
        auto x = mp + s * rotate(bm, 0.78);
        auto y = mp + s * rotate(bm, -0.78);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(mp[0], mp[1]);
        glVertex2f(x[0], x[1]);
        glVertex2f(y[0], y[1]);
        glEnd();
    }
}

void draw(std::list<georhiau::vertex<double, 2>>& ps) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    auto params = projection_params(ps);

    glOrtho(0.0f, params.first * (1.01), 0.0f, params.second * (1.01), 0.f,
            1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    for (const auto& p : ps) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBegin(GL_POINTS);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(p[0], p[1]);
        glEnd();
    }
}

template <typename prim>
bool run(GLFWwindow* window, std::list<prim>& p) {
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.98f, 0.98f, 0.98f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        draw(p);

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

auto plot(std::list<georhiau::triangle<double>>& tris) {
    auto window = get_window();
    if (window) {
        auto finished = run(window, tris);
    }
    exit(window);
}

auto plot(std::list<georhiau::edge<double, 2>>& es) {
    auto window = get_window();
    if (window) {
        auto finished = run(window, es);
    }
    exit(window);
}

auto plot(std::list<georhiau::vertex<double, 2>>& ps) {
    auto window = get_window();
    if (window) {
        auto finished = run(window, ps);
    }
    exit(window);
}

}  // namespace georhiau
