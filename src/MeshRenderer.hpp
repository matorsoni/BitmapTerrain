#ifndef MESH_RENDERER_HPP
#define MESH_RENDERER_HPP

// Forward declarations to avoid unnecessary `include`.
class Camera;
class Mesh;
class ShaderProgram;

class MeshRenderer
{
public:
    MeshRenderer();

    void updateMesh(const Mesh& mesh);
    void draw(Camera& camera, const ShaderProgram& program) const;

private:
    // Reference to the mesh that will be rendered.
    const Mesh* mesh_ptr_;

    // Render on wireframe.
    bool wireframe_;

    // OpenGL object handles: Vertex Array Object, Vertex Buffer Object, Element Buffer Object.
    unsigned int vao_;
    unsigned int vbo_;
    unsigned int ebo_;
};

#endif // MESH_RENDERER_HPP
