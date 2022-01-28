#include <vector>

#include "glad/glad.h"

#include "shader_program.hpp"

ShaderProgram::ShaderProgram(const std::vector<Shader> &shaders) : m_programHandle(0) {
    m_programHandle = glCreateProgram();
    std::for_each(std::begin(shaders), std::end(shaders), [this] (const Shader &shader) {
        glAttachShader(m_programHandle, shader.openglHandle());
    });
    glLinkProgram(m_programHandle);
    verifyProgramLinked();
}

ShaderProgram::~ShaderProgram() {
    if (0 != m_programHandle) {
        glDeleteProgram(m_programHandle);
    }
}

void ShaderProgram::use() {
    glUseProgram(m_programHandle);
}

void ShaderProgram::setBool(const std::string &name, bool value) {
    glUniform1i(glGetUniformLocation(m_programHandle, name.c_str()), (int)value);
}

void ShaderProgram::setInt(const std::string &name, int value) {
    glUniform1i(glGetUniformLocation(m_programHandle, name.c_str()), value);
}

void ShaderProgram::setFloat(const std::string &name, float value) {
    glUniform1f(glGetUniformLocation(m_programHandle, name.c_str()), value);
}


void ShaderProgram::verifyProgramLinked() {
    GLint ok;
    constexpr std::size_t infoLogSize = 1024;
    std::string infoLog;

    glGetProgramiv(m_programHandle, GL_LINK_STATUS, &ok);
    if (!ok) {
        infoLog.resize(infoLogSize);
        glGetProgramInfoLog(m_programHandle, infoLogSize, NULL, infoLog.data());
        throw std::runtime_error("Program linkage failed. Info: " + infoLog);
    }
}
