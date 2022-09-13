#include "MeshRenderer.hpp"

#include <iostream>

#include <glad/glad.h>

#include "Camera.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"

using std::cout;
using std::endl;

MeshRenderer::MeshRenderer():
    mesh_ptr_(nullptr),
    tex_ptr_(nullptr),
    shader_color_("../src/shader/Vert.glsl",
                  "../src/shader/Frag.glsl"),
    shader_texture_("../src/shader/Vert_Texture.glsl",
                     "../src/shader/Frag_Texture.glsl"),
    wireframe_(true),
    textured_(true),
    yscale_(3.0f),
    vao_(0), vbo_(0), ebo_(0)
{
    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);
    glGenBuffers(1, &ebo_);

    // Set background color.
    glClearColor(0.0f, 0.15f, 0.15, 1.0f);
    glEnable(GL_DEPTH_TEST);

    // Log useful info.
    cout << "OpenGL version " << glGetString(GL_VERSION) << endl;
    cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
    cout << "OpenGL renderer: " << glGetString(GL_RENDERER) << endl;
    cout << "OpenGL vendor: " << glGetString(GL_VENDOR) << endl;
}

void MeshRenderer::pushMesh(const Mesh& mesh)
{
    // Populate OpenGL's VAO and pass vertex data to the GPU.
    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER,
                 mesh.vertices.size() * sizeof(Vertex),
                 mesh.vertices.data(),
                 GL_STATIC_DRAW);

    // Position data on layout 0 for the vertex shader.
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    // Texture data on layout 1 for the vertex shader.
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 mesh.indices.size() * sizeof(unsigned int),
                 mesh.indices.data(),
                 GL_STATIC_DRAW);

    mesh_ptr_ = &mesh;
    glBindVertexArray(0);
}

void MeshRenderer::setTexture(const Texture& texture)
{
    tex_ptr_ = &texture;
}

void MeshRenderer::draw(Camera& camera) const
{
    assert(mesh_ptr_);
    assert(tex_ptr_);

    // Model transformation to change the mesh's position in space.
    static glm::mat4 model(1.0f);
    model[1][1] = yscale_;

    // Select shader program.
    const ShaderProgram& shader = textured_ ? shader_texture_ : shader_color_;
    shader.use();
    if (textured_) {
        tex_ptr_->bind();
        shader.setUniform1i("tex_sampler", 0);
    }
    shader.setUniformMat4f("Model", model);
    shader.setUniformMat4f("View", camera.view());
    shader.setUniformMat4f("Projection", camera.projection());

    // Render on wireframe or fill mode.
    glPolygonMode(GL_FRONT_AND_BACK, wireframe_ ? GL_LINE : GL_FILL);

    // Render mesh.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, mesh_ptr_->indices.size(), GL_UNSIGNED_INT, (void*)0);

    // Unbind VAO after finishing.
    glBindVertexArray(0);
}

void MeshRenderer::toggleWireframeOnOff()
{
    wireframe_ = !wireframe_;
}

void MeshRenderer::toggleTextureOnOff()
{
    textured_ = !textured_;
}

void MeshRenderer::controlYScale(float delta)
{
    static constexpr float lower_bound = 0.2f;
    static constexpr float upper_bound = 6.0f;

    yscale_ += delta;
    if (yscale_ < lower_bound) {
        yscale_ = lower_bound;
    }
    else if (yscale_ > upper_bound) {
        yscale_ = upper_bound;
    }
}
