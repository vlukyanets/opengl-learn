#ifndef __WINDOW_MANAGER_HPP__
#define __WINDOW_MANAGER_HPP__

#include <map>
#include <functional>
#include <type_traits>

class WindowManager final {
public:
    using FramebufferSizeCallback = std::add_pointer<void(GLFWwindow *, int, int)>::type;
    using RenderLoopCallback = std::function<void()>;

public:
    WindowManager(int openglMajorVersion, int openglMinorVersion, int openglProfile);
    ~WindowManager();

    GLFWwindow *createWindow(
        int width, int height, const std::string &name,
        FramebufferSizeCallback framebufferSizeCallback,
        RenderLoopCallback renderLoopCallback,
        bool make_current = true);

    void destroyWindow(GLFWwindow *window);

private:
    WindowManager(const WindowManager &) = delete;
    WindowManager &operator=(const WindowManager &) = delete;

private:
    std::map<GLFWwindow *, RenderLoopCallback> m_windows;
};

#endif /* __WINDOW_MANAGER_HPP__ */
