#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include <string>

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
};


#endif // SHADER_PROGRAM_HPP
