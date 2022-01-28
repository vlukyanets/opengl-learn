#ifndef __SHADER_PROGRAM_HPP__
#define __SHADER_PROGRAM_HPP__

#include <vector>

#include "shader.hpp"

class ShaderProgram {
public:
    ShaderProgram(const std::vector<Shader> &shaders);
    virtual ~ShaderProgram();

    void use();

    void setBool(const std::string &name, bool value);
    void setInt(const std::string &name, int value);
    void setFloat(const std::string &name, float value);

private:
    void verifyProgramLinked();

private:
    ShaderProgram(const ShaderProgram &) = delete;
    ShaderProgram &operator=(const ShaderProgram &) = delete;

private:
    GLuint m_programHandle;
};

#endif /* __SHADER_PROGRAM_HPP__ */
