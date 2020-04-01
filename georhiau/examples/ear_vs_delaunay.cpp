#include <GLFW/glfw3.h>
#include <iostream>
#include <list>
#include <random>

#include "algo/delaunay.hpp"
#include "core/triangle.hpp"

static void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action,
                         int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void grid(int w, int h) {
    int W = w / 10;
    int H = h / 10;

    for (float i = 0; i < W; i++) {
        glBegin(GL_LINES);
        glColor3f(0.9f, 0.9f, 0.9f);
        glVertex2f((i * 10), 0.f);
        glVertex2f((i * 10), 1.0f * w);
        glEnd();
    }

    for (float i = 0; i < H; i++) {
        glBegin(GL_LINES);
        glColor3f(0.9f, 0.9f, 0.9f);
        glVertex2f(0.f, (i * 10));
        glVertex2f(1.0f * h, (i * 10));
        glEnd();
    }

    glBegin(GL_LINES);
    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex2f(0.f, 0.f);
    glVertex2f(0.f, 1.0f * h);
    glVertex2f(0.f, 0.f);
    glVertex2f(1.0f * w, 0.f);
    glEnd();
}

void draw_triangles(std::list<georhiau::core::triangle<double>>& tris) {
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

        // DRAW STUFF
        int w, h;
        glfwGetFramebufferSize(window, &w, &h);
        grid(w, h);

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

auto get_window(int w, int h, const char* title) {
    glfwSetErrorCallback(error_callback);
    glfwInit();
    auto window = glfwCreateWindow(w, h, title, nullptr, nullptr);
    if (!window) {
        return window;
    }

    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, 0.f, 100.f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPointSize(5);

    return window;
}

auto plot(std::list<georhiau::core::triangle<double>>& tris) {
    auto window = get_window(1000, 1000, "Delaunay vs. Ear-Clipping");
    if (window) {
        auto finished = run(window, tris);
    }
    exit(window);
}

int main() {
    using vtx = georhiau::core::vertex<double, 2>;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<> dist(0.1, 999.9);

    std::vector<vtx> cloud;

    for (std::size_t i = 0; i < 100; ++i) {
        double x = dist(rng);
        double y = dist(rng);
        vtx v{x,y};
        cloud.push_back(v);
    }

    auto tris = georhiau::algo::delaunay(cloud);

    plot(tris);

    std::cout << "hello" << std::endl;
}

