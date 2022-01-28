#include <string>
#include <stdexcept>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "window_manager.hpp"

WindowManager::WindowManager(int openglMajorVersion, int openglMinorVersion, int openglProfile) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, openglMajorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, openglMinorVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, openglProfile);
}

WindowManager::~WindowManager() {
    std::for_each(std::begin(m_windows), std::end(m_windows), [] (GLFWwindow *window) {
        glfwDestroyWindow(window);
    });
    glfwTerminate();
}

GLFWwindow *WindowManager::createWindow(
    int width, int height, const std::string &name,
    FramebufferSizeCallback framebufferSizeCallback,
    RenderLoopCallback renderLoopCallback,
    bool make_current
) {
    GLFWwindow *window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
    if (NULL == window) {
        throw std::runtime_error("Failed to create GLFW window");
    }

    if (make_current) {
        glfwMakeContextCurrent(window);
    }
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    m_windows.insert(std::make_pair(window, renderLoopCallback));
    return window;
}

void WindowManager::destroyWindow(GLFWwindow *window) {
    if (!m_windows.contains(window)) {
        throw std::runtime_error("Failed to delete GLFW window");
    }

    glfwDestroyWindow(window);
    m_windows.erase(window);
}
