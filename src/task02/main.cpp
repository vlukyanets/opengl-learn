#include <iostream>
#include <filesystem>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "shader.hpp"
#include "shader_program.hpp"
#include "window_manager.hpp"

void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void renderLoop()

int main(int argc, char *argv[]) {
    WindowManager windowManager(3, 3, GLFW_OPENGL_CORE_PROFILE);
    auto window = windowManager.createWindow(800, 600, "Learn OpenGL", framebufferSizeCallback);

    auto shaderFolder = std::filesystem::path(argv[0]);
    shaderFolder = shaderFolder.parent_path().parent_path() / "shaders";

    std::unique_ptr<ShaderProgram> shaderProgramPtr;

    {
        std::vector<Shader> shaders;
        shaders.emplace_back(shaderFolder / "vertex_shader_01.glsl", GL_VERTEX_SHADER);
        shaders.emplace_back(shaderFolder / "fragment_shader_01.glsl", GL_FRAGMENT_SHADER);
        shaderProgramPtr = make_unique<ShaderProgram>(shaders);
    }

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    return 0;
}

void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}
