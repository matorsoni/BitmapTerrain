#ifndef MESH_RENDERER_HPP
#define MESH_RENDERER_HPP

// Forward declarations to avoid unnecessary `include`.
class Camera;
class Mesh;
class ShaderProgram;
class Texture;

class MeshRenderer
{
public:
    MeshRenderer();

    // Set reference to the mesh that will be rendered and send data to the GPU.
    void pushMesh(const Mesh& mesh);
    void setTexture(const Texture& texture);

    // Render mesh.
    void draw(Camera& camera, const ShaderProgram& program) const;

    // Switch wireframe mode on and off.
    void toggleWireframeOnOff();

private:
    // Reference to the mesh that will be rendered.
    const Mesh* mesh_ptr_;
    const Texture* tex_ptr_;

    // Render on wireframe.
    bool wireframe_;

    // OpenGL object handles: Vertex Array Object, Vertex Buffer Object, Element Buffer Object.
    unsigned int vao_;
    unsigned int vbo_;
    unsigned int ebo_;
};

#endif // MESH_RENDERER_HPP
