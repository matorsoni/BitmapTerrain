#include "MeshRenderer.hpp"

#include <iostream>

#include <glad/glad.h>

#include "Camera.hpp"
#include "Mesh.hpp"
#include "ShaderProgram.hpp"

using std::cout;
using std::endl;

MeshRenderer::MeshRenderer():
    mesh_ptr_(nullptr),
    wireframe_(true),
    vao_(0), vbo_(0), ebo_(0)
{
    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);
    glGenBuffers(1, &ebo_);

    // Set background color.
    glClearColor(0.0f, 0.15f, 0.15, 1.0f);

    // Log useful info.
    cout << "OpenGL version " << glGetString(GL_VERSION) << endl;
    cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
    cout << "OpenGL renderer: " << glGetString(GL_RENDERER) << endl;
    cout << "OpenGL vendor: " << glGetString(GL_VENDOR) << endl;
}

void MeshRenderer::updateMesh(const Mesh& mesh)
{
    // Populate OpenGL's VAO and pass vertex data to the GPU.
    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER,
                 mesh.vertices.size() * sizeof(Vertex),
                 mesh.vertices.data(),
                 GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 mesh.indices.size() * sizeof(unsigned int),
                 mesh.indices.data(),
                 GL_STATIC_DRAW);

    mesh_ptr_ = &mesh;
    glBindVertexArray(0);
}

void MeshRenderer::draw(Camera& camera, const ShaderProgram& program) const
{
    assert(mesh_ptr_ != nullptr);

    // Static declaration of `model` transformation since we are not moving the mesh's position.
    static glm::mat4 model(1.0f);

    // Update camera's internal matrices.
    camera.updateView();

    program.use();
    program.setUniformMat4f("Model", model);
    program.setUniformMat4f("View", camera.view());
    program.setUniformMat4f("Projection", camera.projection());

    // Render on wireframe or fill mode.
    glPolygonMode(GL_FRONT_AND_BACK, wireframe_ ? GL_LINE : GL_FILL);

    // Render mesh.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, mesh_ptr_->indices.size(), GL_UNSIGNED_INT, (void*)0);

    // Unbind VAO after finishing.
    glBindVertexArray(0);
}