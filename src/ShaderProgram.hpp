#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include <string>

#include <glm/mat4x4.hpp>

// Class abstraction for OpenGL shader program object.
class ShaderProgram
{
private:
    unsigned int id_;

public:
    ShaderProgram(const std::string& vert_shader_path,
                  const std::string& frag_shader_path);
    ~ShaderProgram() = default;

    // Get shader program id.
    unsigned int getId() const;
    // Use program shader.
    void use() const;

    // Set uniforms.
    void setUniformMat4f(const char* uniform_name, const glm::mat4& mat) const;
};


#endif // SHADER_PROGRAM_HPP
