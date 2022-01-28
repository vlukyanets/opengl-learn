#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include "glad/glad.h"

#include "shader.hpp"

Shader::Shader(const std::filesystem::path &path, Shader::Type type) : m_shaderHandle(0) {
    std::string shaderContent;
    try {
        std::ifstream file{path.string()};
        file.exceptions(std::ifstream::badbit | std::ifstream::failbit);
        shaderContent.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    } catch (const std::ifstream::failure &) {
        throw std::runtime_error("Failed to read shader from " + path.string());
    } catch (const std::exception &) {
        throw std::runtime_error("Unknown error during read " + path.string());
    }

    m_shaderHandle = glCreateShader(type);
    if (0 == m_shaderHandle) {
        throw std::runtime_error("Failed to create shader of type " + std::to_string(type));
    }

    auto shaderSourcePtr = shaderContent.c_str();
    glShaderSource(m_shaderHandle, 1, &shaderSourcePtr, NULL);
    glCompileShader(m_shaderHandle);
    verifyShaderCompiled();
}

Shader::~Shader() {
    if (0 != m_shaderHandle) {
        glDeleteShader(m_shaderHandle);
    }
}

Shader::Shader(Shader &&other) {
    std::swap(m_shaderHandle, other.m_shaderHandle);
}

Shader& Shader::operator= (Shader &&other) {
    std::swap(m_shaderHandle, other.m_shaderHandle);
    return *this;
}

void Shader::verifyShaderCompiled() {
    GLint ok;
    constexpr std::size_t infoLogSize = 1024;
    std::string infoLog;

    glGetShaderiv(m_shaderHandle, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        infoLog.resize(infoLogSize);
        glGetShaderInfoLog(m_shaderHandle, infoLogSize, NULL, infoLog.data());
        throw std::runtime_error("Shader compilation failed. Info" + infoLog);
    }
}
