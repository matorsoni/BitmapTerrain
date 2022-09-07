#include "ShaderProgram.hpp"

#include <fstream>
#include <iostream>

#include <glad/glad.h>

using namespace std;

// Load shader source from the disk.
static string loadShaderSource(const string& filename)
{
    string text, line;
    ifstream file(filename);
    if (!file) {
        cout << "Unable to read file " << filename << endl;
        return {};
    }

    while (getline(file, line)) {
        text.append(line + "\n");
    }

    return text;
}


// ShaderProgram class implementation.
ShaderProgram::ShaderProgram(const string& vert_shader_path,
                             const string& frag_shader_path):
    id_{0}
{
    // Load vertex shader source and compile it.
    string vert_shader_string = loadShaderSource(vert_shader_path);
    const char* vert_shader_src = vert_shader_string.c_str();
    unsigned int vert_shader_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert_shader_id, 1, &vert_shader_src, NULL);
    glCompileShader(vert_shader_id);

    // Load fragment shader source and compile it.
    string frag_shader_string = loadShaderSource(frag_shader_path);
    const char* frag_shader_src = frag_shader_string.c_str();
    unsigned int frag_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag_shader_id, 1, &frag_shader_src, NULL);
    glCompileShader(frag_shader_id);

    // Check if shaders compiled correctly.
    {
        int success;
        char info_log[512];

        glGetShaderiv(vert_shader_id, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vert_shader_id, 512, NULL, info_log);
            cout << "Vertex shader compilation failed: \n" << info_log << endl;
        }

        glGetShaderiv(frag_shader_id, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(frag_shader_id, 512, NULL, info_log);
            cout << "Fragment shader compilation failed: \n" << info_log << endl;
        }
    }

    // Link shader program.
    id_ = glCreateProgram();
    glAttachShader(id_, vert_shader_id);
    glAttachShader(id_, frag_shader_id);
    glLinkProgram(id_);

    // Check if linking went well.
    {
        int success;
        char info_log[512];
        glGetProgramiv(id_, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(id_, 512, NULL, info_log);
            cout << "Shader program linking failed: \n" << info_log << endl;
        }
    }

    // Delete intermediate shader objects.
    glDeleteShader(vert_shader_id);
    glDeleteShader(frag_shader_id);
}

unsigned int ShaderProgram::getId() const
{
    return id_;
}

void ShaderProgram::use() const
{
    glUseProgram(id_);
}
