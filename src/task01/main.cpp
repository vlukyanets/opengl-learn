#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window) {
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, true);
    }
}

const std::string vertex_shader_src =
    "#version 330 core\n"
    "layout (location=0) in vec3 aPos;\n"
    "layout (location=1) in vec3 aColor;\n"
    "out vec3 testColor;\n"
    "void main() {\n"
    "  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "  testColor = aColor;\n"
    "}\n";

const std::string fragment_shader_src =
    "#version 330 core\n"
    "out vec4 fragColor;\n"
    "in vec3 testColor;\n"
    "void main() {\n"
    "  fragColor = vec4(testColor, 1.0f);\n"
    "}\n";

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);
    if (NULL == window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar * const vertex_shader_cstr = static_cast<const GLchar *>(vertex_shader_src.c_str());
    glShaderSource(vertex_shader, 1, &vertex_shader_cstr, NULL);
    glCompileShader(vertex_shader);

    {
        int success;
        char info_log[512];
        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
            std::cout << "Failed to compile vertex shader: " << info_log << std::endl;
        }
    }

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar * const fragment_shader_cstr = static_cast<const GLchar *>(fragment_shader_src.c_str());
    glShaderSource(fragment_shader, 1, &fragment_shader_cstr, NULL);
    glCompileShader(fragment_shader);

    {
        int success;
        char info_log[512];
        glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
            std::cout << "Failed to compile fragment shader: " << info_log << std::endl;
        }
    }

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    {
        int success;
        char info_log[512];
        glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader_program, 512, NULL, info_log);
            std::cout << "Failed to link shader program: " << info_log << std::endl;
        }
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    float vertices[] = {
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
    };

    GLuint vbo, vao;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)NULL);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // glBindBuffer(GL_ARRAY_BUFFER, 0);

    glUseProgram(shader_program);

    while (!glfwWindowShouldClose(window)) {
        process_input(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shader_program);
    glfwTerminate();
    return 0;
}
