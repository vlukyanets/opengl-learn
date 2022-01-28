#ifndef __SHADER_HPP__
#define __SHADER_HPP__

#include <filesystem>

class Shader {
public:
    using Type = GLenum;

public:
    Shader(const std::filesystem::path &path, Shader::Type type);
    virtual ~Shader();

    Shader(Shader &&other);
    Shader& operator= (Shader &&other);

    GLuint openglHandle() const {
        return m_shaderHandle;
    }

private:
    void verifyShaderCompiled();

private:
    Shader(const Shader &);
    Shader& operator= (const Shader &);

private:
    GLuint m_shaderHandle;
};

#endif /* __SHADER_HPP__ */
