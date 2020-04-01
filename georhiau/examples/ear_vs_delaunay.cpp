#include <GLFW/glfw3.h>
#include <iostream>

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

bool run(GLFWwindow* window) {
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.98f, 0.98f, 0.98f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // DRAW STUFF
        int w,h;
        glfwGetFramebufferSize(window, &w, &h);
        grid(w, h);

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

auto plotter() {
    auto window = get_window(800, 800, "Delaunay vs. Ear-Clipping");
    if (window) {
        auto finished = run(window);
    }
    exit(window);
}

int main() {
    plotter();
    std::cout << "hello" << std::endl;
}

