#ifndef MESH_RENDERER_HPP
#define MESH_RENDERER_HPP

#include "ShaderProgram.hpp"

// Forward declarations to avoid unnecessary `include`.
class Camera;
class Mesh;
class Texture;

class MeshRenderer
{
public:
    MeshRenderer();

    // Set reference to the mesh that will be rendered and send data to the GPU.
    void pushMesh(const Mesh& mesh);
    void setTexture(const Texture& texture);

    // Render mesh.
    void draw(Camera& camera) const;

    // Switch wireframe mode on and off.
    void toggleWireframeOnOff();
    // Switch textured render mode on and off.
    void toggleTextureOnOff();
    // Increase or decrease Y scaling factor.
    void controlYScale(float delta);

private:
    // Reference to the mesh that will be rendered.
    const Mesh* mesh_ptr_;
    const Texture* tex_ptr_;

    // Shader programs.
    ShaderProgram shader_color_;
    ShaderProgram shader_texture_;

    // Render on wireframe.
    bool wireframe_;
    // Render textured or colored.
    bool textured_;
    // Y scaling factor.
    float yscale_;

    // OpenGL object handles: Vertex Array Object, Vertex Buffer Object, Element Buffer Object.
    unsigned int vao_;
    unsigned int vbo_;
    unsigned int ebo_;
};

#endif // MESH_RENDERER_HPP
